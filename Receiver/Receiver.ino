#include <SPI.h>
#include <RH_RF95.h>
#include <RHEncryptedDriver.h>
#include <AES.h>
#include <EEPROM.h>
#include <Crypto.h>
#include <SHA256.h>

#define RECEIVE_BUFFER_SIZE 5
#define MESSAGELENGTH 30
#define EEPROM_START_ADDR 0
#define MAX_USERS 2
#define MAX_USERNAME_LENGTH 8
#define SHA256_BLOCK_SIZE 32

struct Msg {
  uint8_t seq;
  char content[MESSAGELENGTH];
  int rssi;
  uint8_t senderID;
  uint8_t destID;
};

Msg rcvBuffer[RECEIVE_BUFFER_SIZE];
int bufIdx = 0;

struct User {
  char username[MAX_USERNAME_LENGTH];
  uint8_t pwdHash[SHA256_BLOCK_SIZE];
};

User users[MAX_USERS];

RH_RF95 rf95;
AESSmall128 myCipher;
RHEncryptedDriver myDriver(rf95, myCipher);

const uint8_t encryptkey[16] = "abcdabcdabcdabcd";
uint8_t RECEIVER_ID = 1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Receiver V1");
  while (!Serial) {}

  if (!rf95.init()) {
    Serial.println("LoRa init failed");
    while (1) { delay(1000); }
  }

  rf95.setFrequency(915.0);
  rf95.setTxPower(23, false);
  rf95.setSignalBandwidth(500000);
  rf95.setSpreadingFactor(12);
  myCipher.setKey(encryptkey, sizeof(encryptkey));
  Serial.println("Setup done");
  initUsers();
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readString();
    char d1 = data.charAt(0);

    if (d1 == 'l') {
      char charArray[data.length() + 1];
      data.toCharArray(charArray, sizeof(charArray));
      char *token = strtok(charArray, ":");
      String username, password;
      int count = 0;
      while (token != NULL) {
        if (count == 1) username = String(token);
        else if (count == 2) password = String(token);
        token = strtok(NULL, ":");
        count++;
      }
      Serial.println(checkLogin(username.c_str(), password.c_str()) ? "login 1" : "login 0");
    }

    if (d1 == 'r') {
      RECEIVER_ID = data.substring(2).toInt();
      Serial.print("Receiver ID: ");
      Serial.println(RECEIVER_ID);
    }
  }

  if (myDriver.available()) {
    uint8_t buf[myDriver.maxMessageLength()];
    uint8_t len = sizeof(buf);

    if (myDriver.recv(buf, &len)) {
      buf[len] = '\0';
      uint8_t seq, type, tagID, relayID, ttl, rssi, senderID, destID;
      char content[MESSAGELENGTH];

      if (sscanf((char *)buf, "%5hhu %5hhu %5hhu %5hhu %5hhu %5hhu %5hhu %5hhu %[^\n]",
                 &seq, &type, &tagID, &relayID, &ttl, &rssi, &senderID, &destID, content) == 9) {
        if (destID == RECEIVER_ID) {
          Serial.print("Seq: "); Serial.print(seq);
          Serial.print(" Sender: "); Serial.print(senderID);
          Serial.print(" RSSI: "); Serial.print(myDriver.lastRssi());
          Serial.print(" message "); Serial.println(content);
          
        } else if (--ttl > 0) {
          sprintf((char *)buf, "%5d %5d %5d %5d %5d %5d %5d %5d %s", seq, type, tagID, relayID, ttl, rssi, senderID, destID, content);
          len = strlen((char *)buf);
          Serial.println("Rebroadcasting...");
          rebroadcastMessage(buf, len);
        } else {
          Serial.println("Expired!");
        }
      } else {
        Serial.println("Parse fail");
      }
    } else {
      Serial.println("recv fail");
    }
  }
}

void rebroadcastMessage(uint8_t *buf, uint8_t len) {
  rf95.setModeIdle();
  while (myDriver.isChannelActive()) { delay(10); }
  myDriver.send(buf, len);
  myDriver.waitPacketSent();
}

void initUsers() {
  for (int i = 0; i < MAX_USERS; i++) {
    EEPROM.get(EEPROM_START_ADDR + i * sizeof(User), users[i]);
  }
  if (isEEPROMBlank()) {
    strcpy(users[0].username, "user");
    hashPassword("password", users[0].pwdHash);
    strcpy(users[1].username, "gohil");
    hashPassword("kartavya", users[1].pwdHash);
    for (int i = 0; i < MAX_USERS; i++) {
      EEPROM.put(EEPROM_START_ADDR + i * sizeof(User), users[i]);
    }
  }
}

bool checkLogin(const char *username, const char *password) {
  int userIdx = findUser(username);
  if (userIdx == -1) return false;
  uint8_t inputHash[SHA256_BLOCK_SIZE];
  hashPassword(password, inputHash);
  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
    if (inputHash[i] != users[userIdx].pwdHash[i]) return false;
  }
  return true;
}

int findUser(const char *username) {
  for (int i = 0; i < MAX_USERS; i++) {
    if (strcmp(users[i].username, username) == 0) return i;
  }
  return -1;
}

void hashPassword(const char *password, uint8_t *hash) {
  SHA256 sha256;
  sha256.update((const uint8_t *)password, strlen(password));
  sha256.finalize(hash, SHA256_BLOCK_SIZE);
}

bool isEEPROMBlank() {
  for (int i = 0; i < EEPROM.length(); i++) {
    if (EEPROM.read(i) != 0xFF) return false;
  }
  return true;
}
