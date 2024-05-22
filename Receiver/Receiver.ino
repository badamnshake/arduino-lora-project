#include <SPI.h>
#include <RH_RF95.h>
#include <RHEncryptedDriver.h>
#include <AES.h>
#include <EEPROM.h>
#include <Crypto.h>
#include <SHA256.h>

// Define the EEPROM starting address to store user data
#define EEPROM_START_ADDR 0

// Define the maximum number of users and the length of username and password
#define MAX_USERS 3            // Reduced to save space
#define MAX_USERNAME_LENGTH 8  // Reduced to save space
#define MAX_PASSWORD_LENGTH 8  // Reduced to save space
#define SHA256_BLOCK_SIZE 64   // Correct block size for SHA256

// Struct to hold user data
struct UserData {
  char username[MAX_USERNAME_LENGTH];
  uint8_t passwordHash[SHA256_BLOCK_SIZE];
};

// Array to store user data
UserData users[MAX_USERS];

// Singleton instance of the radio driver
RH_RF95 rf95;
AES128 myCipher;                             // Instanciate a Speck block ciphering
RHEncryptedDriver myDriver(rf95, myCipher);  // Instantiate the driver with those two

const uint8_t encryptkey[16] = "abcdabcdabcdabcd";  // The very secret key

// Message fields
uint8_t SEQ = 0;    // Sequence number
uint8_t TYPE = 0;   // Message type
uint8_t TAGID = 1;  // Identity of tag. Will eventually be read from an SD card.
uint8_t RELAYID = 0;
uint8_t TTL = 5;
uint8_t thisRSSI = 5;
uint8_t firstIteration = 0;  // First time through main loop send a reset (kludge, I know. Should go in setup.

unsigned long TXINTERVAL = 10000;  // Time between transmissions (in ms), increased to 10 seconds
unsigned long lastTransmit = 0;    // Last transmit time

char uMessage[30];  // User message buffer reduced to 30 characters

// to communicate with GUI
String data;
char d1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Receiver Version 1");
  while (!Serial)
    Serial.println("Waiting for serial port");  // Wait for serial port to be available.
  while (!rf95.init()) {
    Serial.println("Initialisation of LoRa receiver failed");
    delay(1000);
  }

  rf95.setFrequency(915.0);
  rf95.setTxPower(23, false);
  rf95.setSignalBandwidth(500000);
  rf95.setSpreadingFactor(12);
  myCipher.setKey(encryptkey, 16);
  Serial.println("Setup completed");
  initializeUsers();
}

void loop() {
  if (Serial.available()) {
    data = Serial.readString();
    d1 = data.charAt(0);

    if (d1 == 'l') {
      char charArray[data.length() + 1];
      data.toCharArray(charArray, sizeof(charArray));

      // Parse the string using strtok()
      char* token = strtok(charArray, ":");
      String login, username, password;

      int count = 0;
      while (token != NULL) {
        if (count == 0) {
          login = String(token);
        } else if (count == 1) {
          username = String(token);
        } else if (count == 2) {
          password = String(token);
        }
        token = strtok(NULL, ":");
        count++;
      }

      // Debugging output
      

      if (checkLogin(username.c_str(), password.c_str())) {
        Serial.println("login 1");
      } else {
        Serial.println("login 0");
      }
    }
  }

  if (myDriver.available()) {
    // Should be a message for us now
    uint8_t buf[myDriver.maxMessageLength()];
    uint8_t len = sizeof(buf);
    if (myDriver.recv(buf, &len)) {
      char str[len];
      strcpy(str, (char*)&buf);
      sscanf(str, "%5d %5d %5d %5d %5d %5d", &SEQ, &TYPE, &TAGID, &RELAYID, &TTL, &thisRSSI);
      memmove(str, str + 36, strlen(str) - 36 + 1);
      // Now display
      Serial.print("Seq ");
      Serial.print(SEQ);
      Serial.print(" Type ");
      Serial.print(TYPE);
      Serial.print(" Tag ");
      Serial.print(TAGID);
      Serial.print(" Relay ");
      Serial.print(RELAYID);
      Serial.print(" TTL ");
      Serial.print(TTL);
      Serial.print(" RSSI ");
      Serial.print(thisRSSI);
      Serial.print(" RSSI ");
      Serial.print(myDriver.lastRssi());
      Serial.println(" ");
      Serial.print(" Message: ");
      Serial.println(str);
      Serial.println(" ");
    } else {
      Serial.println("recv failed");
    }
  }
}

void initializeUsers() {
  // Read user data from EEPROM
  for (int i = 0; i < MAX_USERS; i++) {
    EEPROM.get(EEPROM_START_ADDR + i * sizeof(UserData), users[i]);
  }

  // If EEPROM is blank, initialize with default users (for demonstration purposes)
  if (isEEPROMBlank()) {
    strcpy(users[0].username, "user");
    hashPassword("password", users[0].passwordHash);

    // Debugging output


    // Write default users to EEPROM
    for (int i = 0; i < MAX_USERS; i++) {
      EEPROM.put(EEPROM_START_ADDR + i * sizeof(UserData), users[i]);
    }
  }
}

bool checkLogin(const char* username, const char* password) {
  // Find the user by username
  int userIndex = findUser(username);
  if (userIndex == -1) {
    // User not found
    return false;
  }

  // Compute hash of input password
  uint8_t inputHash[32];  // SHA256 produces 32-byte hashes
  hashPassword(password, inputHash);

  // Debugging output




  // Compare hashes
  for (int i = 0; i < 32; i++) {
    if (inputHash[i] != users[userIndex].passwordHash[i]) {
      // Hashes don't match
      return false;
    }
  }

  return true;
}

int findUser(const char* username) {
  for (int i = 0; i < MAX_USERS; i++) {
    if (strcmp(users[i].username, username) == 0) {
      // User found
      return i;
    }
  }
  // User not found
  return -1;
}

void hashPassword(const char* password, uint8_t* hash) {
  SHA256 sha256;

  // Update the context with the password data
  sha256.update((const uint8_t*)password, strlen(password));

  // Finalize the hash and store it in the provided buffer
  sha256.finalize(hash, 32);
}

bool isEEPROMBlank() {
  for (int i = 0; i < EEPROM.length(); i++) {
    if (EEPROM.read(i) != 0xFF) {
      return false;  // EEPROM is not blank
    }
  }
  return true;  // EEPROM is blank
}
