//Setup RTC

#include "RTClib.h"
RTC_PCF8523 rtc;

//Setup nfc

#include <NfcAdapter.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <Wire.h>
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

//Setup SD-Card

#include "SdFat.h"
#define SD_FAT_TYPE 0 //SD format = Fat32
const uint8_t SD_CS_PIN = 10;
// Try to select the best SD card configuration.
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI)
SdFat sd;
File file;
File myFile;
char line[21];

//Setup SPI
 
#include <SPI.h>
char UID2 [21];
String UID;

//Setup Feedback loop

long interval = 2000;
long prevTime = 1000;
int sensorValue = 0;

//rotor control

const int stepPin = 9; 
const int dirPin = 8; 


void setup() {
  // put your setup code here, to run once:


pinMode(2, OUTPUT);      //steppercontrol-Enable
pinMode(4, INPUT);       //red-button
pinMode(5, INPUT);       //green-button
pinMode(6, OUTPUT);      //green-led
pinMode(7, OUTPUT);      //red-led
pinMode(10, OUTPUT);     //SD-CS
pinMode(stepPin,OUTPUT); //steppercontrol-step
pinMode(dirPin,OUTPUT);  //steppercontrol-direction
pinMode(A0, OUTPUT);     //buzzer
pinMode(A1, INPUT);      //lockstatus-potentiometer
pinMode(A4, INPUT);
pinMode(A5, INPUT);
digitalWrite(stepPin, LOW);
digitalWrite(dirPin, LOW);
digitalWrite(2, HIGH);

Serial.begin(9600);
Serial.println("NDEF Reader");
nfc.begin();


}

void loop() {
 

while (nfc.tagPresent()) {    //scanning for NFC-Tag
   NfcTag tag = nfc.read();   
   Serial.println(tag.getUidString());
   }


sensorValue = analogRead(A1); //watching lockstate
Serial.print("lockstatus");
Serial.println(sensorValue);
delay(10);
if(sensorValue <= 840){        //turn on green LED/turn off red LED when lock open
   digitalWrite(6, LOW);
   digitalWrite(7, HIGH);
}
if(sensorValue > 840){         //turn on red LED/turn off green LED when lock closed
   digitalWrite(6, HIGH);
   digitalWrite(7, LOW);
   }

}
