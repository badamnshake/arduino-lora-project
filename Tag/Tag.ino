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
#define MAX_USERS 3
#define SHA256_BLOCK_SIZE 64


// Struct to hold user data
struct UserData {
  char username[8];
  uint8_t passwordHash[SHA256_BLOCK_SIZE];
};

// Array to store user data
UserData users[MAX_USERS];

// Singleton instance of the radio driver
RH_RF95 rf95;
AESSmall128 myCipher;                        // Instantiate AES block ciphering
RHEncryptedDriver myDriver(rf95, myCipher);  // Instantiate the driver with those two
int led = 13;                                // Define LED pin in case we want to use it to demonstrate activity

unsigned char encryptkey[16] = "abcdabcdabcdabcd";  // The very secret key

// Message fields
int SEQ = 0;    // Sequence number
int TYPE = 0;   // Message type
int TAGID = 1;  // Identity of tag. Will eventually be read from an SD card.
int RELAYID = 0;
int TTL = 5;
int thisRSSI = 0;
int firstIteration = 0;  // First time through main loop send a reset (kludge, I know. Should go in setup.

int MESSAGELENGTH = 100;
unsigned long TXINTERVAL = 10000;  // Time between transmissions (in ms), increased to 10 seconds
double CSMATIME = 10;              // Check the status of the channel every 10 ms
unsigned long lastTransmit = 0;    // Last transmit time

char uMessage[100];  // User message buffer increased to 100 characters

// to communicate with GUI
String data;
char d1;
// look at loop
void setup() {
  // Initialise LoRa transceiver
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Tag version 1");
  while (!Serial)
    Serial.println("Waiting for serial port");  // Wait for serial port to be available.
  while (!rf95.init()) {
    Serial.println("Initialisation of LoRa receiver failed");
    delay(1000);
  }
  rf95.setFrequency(915.0);  // PB set to use 915 MHz
  rf95.setTxPower(5, false);
  myCipher.setKey(encryptkey, sizeof(encryptkey));
  rf95.setSignalBandwidth(500000);
  rf95.setSpreadingFactor(12);
  initializeUsers();
}

void loop() {
  unsigned long currentMillis = millis();



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

      if (checkLogin(username.c_str(), password.c_str())) {
        Serial.println("login 1");

      } else {
        Serial.println("login 0");
      }
    }

    if (d1 == 's') {
      data = data.substring(5);
      // Read the incoming message

      data.toCharArray(uMessage, sizeof(uMessage));


      // char* token = strtok(uMessage, ":");
      // String s, message;

      // int count = 0;
      // while (token != NULL) {
      //   if (count == 0) {
      //     s = String(token);
      //   } else if (count == 1) {
      //     message = String(token);
      //   }
      //   token = strtok(NULL, ":");
      //   count++;
      // }

      // message.toCharArray(uMessage, sizeof(uMessage));

      // memset(uMessage, 0, sizeof(uMessage));                                          // Clear the previous message
      int messageSize = data.length();  // Read new message
      // uMessage[messageSize] = '\0';                                                   // Ensure null-termination
      if (messageSize > 0) {
        Serial.print("New message received: ");
        Serial.println(uMessage);
        sendMessage();
        lastTransmit = millis();                // Reset the timer after immediate send
        memset(uMessage, 0, sizeof(uMessage));  // Clear message after sending
      }
    }
  }
}

void sendMessage() {
  if (strlen(uMessage) > 0) {    // Only proceed if the message is not empty
    uint8_t buf[MESSAGELENGTH];  // Use predefined MESSAGELENGTH for the buffer size
    uint8_t len;

    char str[MESSAGELENGTH];  // Use MESSAGELENGTH for str as well
    if (firstIteration == 0)  // Kludge to send out a type 9 as the first message.
    {
      TYPE = 9;
      firstIteration = 1;
    } else
      TYPE = 0;

    SEQ++;
    sprintf(str, "%5d %5d %5d %5d %5d %5d %s", SEQ, TYPE, TAGID, RELAYID, TTL, thisRSSI, uMessage);
    len = strlen(str);  // Get the length of the formatted message

    // Check if the message length exceeds the buffer size
    if (len > MESSAGELENGTH) {
      Serial.println("Message too long!");  // Handle error
      return;                               // Exit function
    }

    // Copy the formatted message to the buffer
    memcpy(buf, str, len);

    rf95.setModeIdle();  // some obscure bug causing loss of every second message

    // Channel should be idle but if not wait for it to go idle
    while (myDriver.isChannelActive()) {
      delay(CSMATIME);                                          // wait for channel to go idle by checking frequently
      Serial.println("Tag node looping on isChannelActive()");  // DEBUG
    }

    // Transmit message
    //Serial.print("Transmitted message: ");  // DEBUG
    //Serial.println((char*)buf);             // DEBUG
    myDriver.send(buf, len);  // Send only the actual message length
    myDriver.waitPacketSent();
  }
}



void initializeUsers() {
  // Read user data from EEPROM
  for (int i = 0; i < MAX_USERS; i++) {
    EEPROM.get(EEPROM_START_ADDR + i * sizeof(UserData), users[i]);
  }
  // Serial.println("EEPROM content before initialization:");
  // for (int i = 0; i < MAX_USERS; i++) {
  //   Serial.print("User ");
  //   Serial.print(i);
  //   Serial.print(": ");
  //   Serial.print(users[i].username);
  //   Serial.print(" - Hash: ");
  //   for (int j = 0; j < SHA256_BLOCK_SIZE; j++) {
  //     Serial.print(users[i].passwordHash[j], HEX);
  //     Serial.print(" ");
  //   }
  //   Serial.println();
  // }

  // If EEPROM is blank, initialize with default users (for demonstration purposes)
  if (isEEPROMBlank()) {
  strcpy(users[0].username, "user");
  hashPassword("password", users[0].passwordHash);
  strcpy(users[1].username, "gohil");
  hashPassword("kartavya", users[1].passwordHash);



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

  // Compare hashes
  for (int i = 0; i < 32; i++) {
    if (inputHash[i] != users[userIndex].passwordHash[i]) {
      // Hashes don't match
      return false;
    }
  }

  // Hashes match
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
  sha256.update(password, strlen(password));

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
