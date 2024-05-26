#include <SPI.h>
#include <RH_RF95.h>
#include <RHEncryptedDriver.h>
#include <AES.h>
#include <EEPROM.h>
#include <Crypto.h>
#include <SHA256.h>

#define RECEIVE_BUFFER_SIZE 5
#define MESSAGELENGTH 50

#define EEPROM_START_ADDR 0
#define MAX_USERS 2
#define MAX_USERNAME_LENGTH 8
#define SHA256_BLOCK_SIZE 32

struct Message {
  uint8_t seq;
  char content[MESSAGELENGTH];
  int rssi;
  uint8_t senderID;
  uint8_t destinationID;
};

Message receiveBuffer[RECEIVE_BUFFER_SIZE];
int bufferIndex = 0;

struct UserData {
  char username[MAX_USERNAME_LENGTH];
  uint8_t passwordHash[SHA256_BLOCK_SIZE];
};

UserData users[MAX_USERS];

RH_RF95 rf95;
AESSmall128 myCipher;  // Instantiate AES block ciphering
RHEncryptedDriver myDriver(rf95, myCipher);  // Instantiate the driver with those two

const uint8_t encryptkey[16] = "abcdabcdabcdabcd";  // The very secret key
uint8_t RECEIVER_ID = 1;  // Default receiver ID

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Receiver Version 1");
  while (!Serial) {
    // Waiting for serial port to be available
  }
  while (!rf95.init()) {
    Serial.println("Initialisation of LoRa receiver failed");
    delay(1000);
  }

  rf95.setFrequency(915.0);
  rf95.setTxPower(23, false);
  rf95.setSignalBandwidth(500000);
  rf95.setSpreadingFactor(12);
  myCipher.setKey(encryptkey, sizeof(encryptkey));
  Serial.println("Setup completed");
  initializeUsers();
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readString();
    char d1 = data.charAt(0);

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

    if (d1 == 'r') {  // Set receiver ID
      RECEIVER_ID = data.substring(2).toInt();
      Serial.print("Receiver ID set to: ");
      Serial.println(RECEIVER_ID);
    }
  }

  if (myDriver.available()) {
    uint8_t buf[myDriver.maxMessageLength()];
    uint8_t len = sizeof(buf);

    if (myDriver.recv(buf, &len)) {
      buf[len] = '\0';  // Null-terminate the message

      uint8_t seq;
      uint8_t type;
      uint8_t tagID;
      uint8_t relayID;
      uint8_t ttl;
      uint8_t rssi;
      uint8_t senderID;
      uint8_t destinationID;
      char content[MESSAGELENGTH];

      int numFields = sscanf((char*)buf, "%5hhu %5hhu %5hhu %5hhu %5hhu %5hhu %5hhu %5hhu %[^\n]", &seq, &type, &tagID, &relayID, &ttl, &rssi, &senderID, &destinationID, content);

      if (numFields == 9) {  // Ensure we got all expected fields
        if (destinationID == RECEIVER_ID) {
          Serial.print("Seq: ");
          Serial.print(seq);
          Serial.print(" Sender: ");
          Serial.println(senderID);
          //Serial.print(" Destination: ");
          //Serial.print(destinationID);
          //Serial.print(" Content: ");
          Serial.println(content);
          Serial.print(" =RSSI: ");
          Serial.println(myDriver.lastRssi());
        } else {
          Serial.println("Message not for this receiver, rebroadcasting...");
          rebroadcastMessage(buf, len);
        }
      } else {
        Serial.println("Failed to parse message");
      }
    } else {
      Serial.println("recv failed");
    }
  }
}

void rebroadcastMessage(uint8_t* buf, uint8_t len) {
  rf95.setModeIdle();  // some obscure bug causing loss of every second message

  // Channel should be idle but if not wait for it to go idle
  while (myDriver.isChannelActive()) {
    delay(10);  // wait for channel to go idle by checking frequently
    Serial.println("Rebroadcast node looping on isChannelActive()");  // DEBUG
  }

  myDriver.send(buf, len);  // Send only the actual message length
  myDriver.waitPacketSent();
  Serial.println("Message rebroadcasted");
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
  uint8_t inputHash[SHA256_BLOCK_SIZE];  // SHA256 produces 32-byte hashes
  hashPassword(password, inputHash);

  // Compare hashes
  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
    if (inputHash[i] != users[userIndex].passwordHash[i]) {
      // Hashes don't match
      return false;
    }
  }

  return true;  // Hashes match
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
  sha256.finalize(hash, SHA256_BLOCK_SIZE);
}

bool isEEPROMBlank() {
  for (int i = 0; i < EEPROM.length(); i++) {
    if (EEPROM.read(i) != 0xFF) {
      return false;  // EEPROM is not blank
    }
  }
  return true;  // EEPROM is blank
}
