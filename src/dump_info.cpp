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

/***
 * Miguel : 9E C1 84 4F  94 08 04 00  02 AC CE 6B  BF 73 06 1D - 201904672
 * Levy   : 53 10 1F 4A  16 08 04 00  03 7B 85 AF  D0 3B 52 90 - 202000144
 * Daniel : 8C AE 51 52  21 08 04 00  02 0A AA 2A  F8 56 62 1D - 201806838
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

    // Dump debug info about the card; PICC_HaltA() is automatically called
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}