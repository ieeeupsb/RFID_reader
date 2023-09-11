#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>

/* https://lastminuteengineers.com/how-rfid-works-rc522-arduino-tutorial/?utm_content=cmp-true
 Pins from Arduino -> Pico
 * 10 -> 5
 * 13 -> 2
 * 11 -> 3
 * 12 -> 4
 * 9  -> 1
 */

#define RST_PIN 22u
#define RFID_CS 17u

MFRC522 mfrc522(RFID_CS, RST_PIN); // Create MFRC522 instance.

void setup()
{
  delay(3000);
  Serial.begin(9600); // Initiate a serial communication

  Serial.println(MISO);
  Serial.println(MOSI);
  Serial.println(SCK);

  Serial.println("Waiting for SPI start!");
  SPI.begin(); // Initiate  SPI bus
  Serial.println("SPI started!");
  mfrc522.PCD_Init(); // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}
void loop()
{
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  // Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "BD 31 15 2B") // change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }

  else
  {
    Serial.println(" Access denied");
    delay(3000);
  }
}