/////
//
// Relay code. Listens for TAG messages, formats them, and retransmits them.
// Also forwards messages from other relays. Length is 25 bytes.
// Message format is
//  SEQ       %5d
//  TYPE (1)  %5dc:\Xampp\htdocs\PHP\tipAssign\arduino-lora-project\Relay\Relay.ino
//  TAGID     %5d
//  RELAYID   %5d
//  TTL       %5d
//  RSSI      %5d
//
/////

#include <SPI.h>
#include <RH_RF95.h>
#include <RHEncryptedDriver.h>
#include <ChaCha.h>

// Singleton instance of radio driver
RH_RF95 rf95;
int led = 13; // Define LED pin in case we want to use it to demonstrate activity
int SEQ;
int TAGID;
int TTL;
int thisRSSI;
char *uMessage;
int RELAYID = 1; // Identity of Relay. Will eventually be read from an SD card.
int RELAY;
int TYPE = 1; // Message type

int MESSAGELENGTH = 36;
int DELAY = 1000;     // Mean time between transmissions (100 milliseconds)
double CSMATIME = 10; // Check the status of the channel every 10 ms

// encryption

ChaCha myCipher;                       // Instanciate a Speck block ciphering
RHEncryptedDriver myDriver(rf95, myCipher); // Instantiate the driver with those two

unsigned char encryptkey[16] = {'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd', 'a', 'b', 'c', 'd'};

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Receiver Version 1");
  while (!Serial)
    Serial.println("Waiting for serial port"); // Wait for serial port to be available.
  while (!rf95.init())
  {
    Serial.println("Initialisation of LoRa receiver failed");
    delay(1000);
  }

  rf95.setFrequency(915.0);
  rf95.setTxPower(23, false);
  rf95.setSignalBandwidth(500000);
  rf95.setSpreadingFactor(12);
  myCipher.setKey(encryptkey, 16);
  Serial.println("Setup completed");
}

void loop()
{
  if (myDriver.available())
  {
    // Should be a message for us now
    uint8_t buf[myDriver.maxMessageLength()];
    uint8_t len = sizeof(buf);
    if (myDriver.recv(buf, &len))
    {
      // Serial.print("Received: ");
      // Serial.println((char *)&buf);
      char str[len];
      strcpy(str, (char *)&buf);
      //      Serial.println(str);
      // Now extract subfields
      sscanf(str, "%5d %5d %5d %5d %5d %5d", &SEQ, &TYPE, &TAGID, &RELAY, &TTL, &thisRSSI);
      memmove(str, str + 36, strlen(str) - 36 + 1);
      // Now display
      Serial.print("Seq ");
      Serial.print(SEQ);
      Serial.print(" Type ");
      Serial.print(TYPE);
      Serial.print(" Tag ");
      Serial.print(TAGID);
      Serial.print(" Relay ");
      Serial.print(RELAY);
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
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  digitalWrite(led, LOW);
}
