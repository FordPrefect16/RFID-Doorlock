
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

long interval = 20000;       //change to wanted waiting time for pressing button
long prevTime = 1000;

//variables for lockstatus

int sensorValue = 0;

//pins

const int stepPin = 9; 
const int dirPin = 8; 


void setup() {


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
digitalWrite(2, HIGH);   //disable Stepper

if (! rtc.begin()) {                                      //begin Real Time Clock script
    abort();
  }
             
if (rtc.lostPower()) {
    Serial.println("No Time set!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));          //adjust time & date to computer time & date after initialisation or powerloss
}
Serial.begin(9600);
Serial.println("NDEF Reader");
nfc.begin();


}

void loop() {
 
Serial.print(digitalRead(3));

while (nfc.tagPresent()) {                                //scanning for NFC-Tag
  NfcTag tag = nfc.read();   
  Serial.println(tag.getUidString());
  UID = tag.getUidString();                               //buffering UserID as string 
  UID.toCharArray(UID2, 21);                              //string UserID to char for comparing to Access.csv    
  Serial.println ("comparing...");
  sd.begin(SD_CONFIG);                                    // Initialize SD-Card -> after changing SD-Card restart is mandatory!
  file.open("Access.csv");                                //open csv file with stored Tags
    while (file.available()) {
      Serial.println("reading line...");
      file.fgets(line, 21);                               //reading UserIDs from file
      if (strcmp(line, UID2)==0){
        file.close();                                     //closing file, & directory
        Serial.println("Access granted");
        digitalWrite(A3, HIGH);                           //short beeping
        delay(10);
        digitalWrite(A3, LOW);
        delay(5);
        prevTime = millis();                              //starting timer 
        while ((millis() - prevTime <= interval)){
          Serial.println("Waiting for button input...");
          if(digitalRead(3) == HIGH) {                    //green button pressed
              Serial.println("Open lock..."); 
              delay(10);
              digitalWrite(2,LOW);                        //enable stepper
              digitalWrite(dirPin,LOW);                   //stepper moves in opening diriction
                for(int x = 0; x < 900; x++) {
                  digitalWrite(stepPin,HIGH); 
                  delayMicroseconds(2000); 
                  digitalWrite(stepPin,LOW); 
                  delayMicroseconds(2000); 
                }
               delay(5000);
               digitalWrite(dirPin,HIGH);                //changes direction after 5 seconds to close latch
                 for(int x = 0; x < 100; x++) {
                  digitalWrite(stepPin,HIGH); 
                  delayMicroseconds(2000); 
                  digitalWrite(stepPin,LOW); 
                  delayMicroseconds(2000); 
                  
                 }
               digitalWrite(2, HIGH);                    //disable stepper
               file.open("Log.csv", FILE_WRITE);         //opening Logging-File
               DateTime now = rtc.now();                 //reading date from RTC, optimize layout and print to Log.csv
               if(now.day()<10){
                file.print("0");
               }
               file.print(now.day(), DEC);
               file.print('-');
               if(now.month()<10){
                 file.print("0");
               }
               file.print(now.month(), DEC);
               file.print('-');
               file.print(now.year(), DEC);
               file.print(" ");
               if(now.hour()<10){
                 file.print("0");
               }
               file.print(now.hour(), DEC);              //reading time from RTC, optimize layout and print to Log.csv
               file.print(':');
               if(now.minute()<10){
                 file.print("0");
               }
               file.print(now.minute(), DEC);
               file.print(':');
               if(now.second()<10){
               file.print("0");
               }
               file.print(now.second(), DEC);
               file.print(" Lock opend by ");            //print action to file
               file.print(UID);                          //print UserID to file
               file.println();
               file.close();                             //close file
               delay(5);
               break;                                    //exit timer loop
         }
          if(digitalRead(4) == HIGH) {                   //red button pressed
             Serial.println("Closing lock...");
             digitalWrite(dirPin,HIGH);                  //changes the rotation direction zo closing
             digitalWrite(2,LOW);                        //enables stepper
              for(int x = 0; x < 900; x++) {
               digitalWrite(stepPin,HIGH); 
               delayMicroseconds(2000); 
               digitalWrite(stepPin,LOW); 
               delayMicroseconds(2000); 
               
             }
          digitalWrite(2, HIGH);                         //disable stepper
          file.open("Log.csv", FILE_WRITE);              //open Logging-File
          DateTime now = rtc.now();                      //reading date from RTC, optimize layout and print to Log.csv
          if(now.day()<10){
            file.print("0");
          }
          file.print(now.day(), DEC);
          file.print('-');
          if(now.month()<10){
            file.print("0");
          }
          file.print(now.month(), DEC);
          file.print('-');
          file.print(now.year(), DEC);
          file.print(" ");
          if(now.hour()<10){
            file.print("0");
          }
          file.print(now.hour(), DEC);                    //reading time from RTC, optimize layout and print to Log.csv
          file.print(':');
          if(now.minute()<10){
            file.print("0");
          }
          file.print(now.minute(), DEC);
          file.print(':');
          if(now.second()<10){
            file.print("0");
          }
          file.print(now.second(), DEC);
          file.print(" Lock closed by ");                //print action to file
          file.print(UID);                               //print UserID to file
          file.println();                      
          file.close();                                  //close file 
          delay(5);   
          break;                                         //exit timmer loop
          } 
        }
     }
      else{
        Serial.println("FALSE");
      }
      
    }
  }
  
sensorValue = analogRead(A1);                           //watching lockstate
Serial.print("Lockstatus: ");
Serial.println(sensorValue);
delay(10);
if(sensorValue <= 840){                                 //turn on green LED/turn off red LED when lock open
   digitalWrite(6, LOW);
   digitalWrite(7, HIGH);
}
if(sensorValue > 840){                                 //turn on red LED/turn off green LED when lock closed
   digitalWrite(6, HIGH);
   digitalWrite(7, LOW);
   }

}
