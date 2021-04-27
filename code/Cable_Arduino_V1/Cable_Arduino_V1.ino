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
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI)
SdFat sd;
File file;
File myFile;
char line[21];

//Setup SPI
 
#include <SPI.h>
char UID2 [21];
String UID;

//Setup Feedback loop

long interval = 20000;
long prevTime = 1000;
int sensorValue = 0;

//rotor control

const int stepPin = 9; 
const int dirPin = 8; 


void setup() {
  // put your setup code here, to run once:


pinMode(2, OUTPUT);      //steppercontrol-Enable
pinMode(3, INPUT);  
pinMode(4, INPUT);       //red-button
pinMode(5, INPUT);       //green-button
pinMode(6, OUTPUT);      //green-led
pinMode(7, OUTPUT);      //red-led
pinMode(10, OUTPUT);     //SD-CS
pinMode(stepPin,OUTPUT); //steppercontrol-step
pinMode(dirPin,OUTPUT);  //steppercontrol-direction
pinMode(A0, OUTPUT);     //buzzer
pinMode(A1, INPUT);      //lockstatus-potentiometer
pinMode(A3, OUTPUT);     //buzzing
pinMode(A4, INPUT);      //NFC-Reader-Input SDA
pinMode(A5, INPUT);      //NFC-Reader-Input SCL
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
  UID = tag.getUidString();
  UID.toCharArray(UID2, 21);
  Serial.println ("comparing...");
  sd.begin(SD_CONFIG); // Initialize SD.
  file.open("Access.csv"); //open csv file with stored Tags
    while (file.available()) {
      Serial.println("reading line...");
      file.fgets(line, 21); //reading Tags from file
      if (strcmp(line, UID2)==0){
        file.close();  //closing file, & directory;H
        Serial.println("Access granted");
        digitalWrite(A3, HIGH);
        delay(10);
        digitalWrite(A3, LOW);
        delay(5);
        prevTime = millis();
        while ((millis() - prevTime <= interval)){
          Serial.println("Waiting for button input...");
          if(digitalRead(3) == HIGH) {  //auf
              Serial.println("Open lock...");
              delay(10);
              digitalWrite(2,LOW);
              digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
                for(int x = 0; x < 900; x++) {
                  digitalWrite(stepPin,HIGH); 
                  delayMicroseconds(2000); 
                  digitalWrite(stepPin,LOW); 
                  delayMicroseconds(2000); 
                }
               delay(5000);
               digitalWrite(dirPin,HIGH); // Makes 200 pulses for making one full cycle rotation
                 for(int x = 0; x < 100; x++) {
                  digitalWrite(stepPin,HIGH); 
                  delayMicroseconds(2000); 
                  digitalWrite(stepPin,LOW); 
                  delayMicroseconds(2000); 
                  
                 }
          digitalWrite(2, HIGH);
          break;
          }
          if(digitalRead(4) == HIGH) {  //zu
             Serial.println("Closing lock...");
             digitalWrite(dirPin,HIGH); //Changes the rotations direction
             digitalWrite(2,LOW);
              for(int x = 0; x < 900; x++) {
               digitalWrite(stepPin,HIGH); 
               delayMicroseconds(2000); 
               digitalWrite(stepPin,LOW); 
               delayMicroseconds(2000); 
               
             }
          digitalWrite(2, HIGH); 
          break; 
          }
        }
     }
      else{
        Serial.println("FALSE");
      }
      
    }
  }
  
sensorValue = analogRead(A1); //watching lockstate
Serial.print("Lockstatus: ");
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
