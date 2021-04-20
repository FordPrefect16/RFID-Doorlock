# RFID-Doorlock
A 3D-printable Doorlock which can attached at a standard door lock cylinder. Opens via RFID-Tag

Aim of this project is to create a electronic doorlock for access control and logging on an sd card. It shall be used on the door of our makerspace. 

The first version of this lock will rely on a wireconnection between outer and inner parts of the lock, hopefully later versions will communicate over radio. STL an CAD files can be found under main.

List of materials (inside mechanics):

- 1x cylinder with key used in door
- 2x bearing F6900 2RS / F 6900 2RS 10x22x6 mm
- 1x bearing 6808 2RS / 61808 2RS 40x52x7 mm
- 1x timing belt GT2 288 mm 
- 1x timing belt GT2 174 mm
- 1x Nema 17 steppermotor 42x20 mm 16 Ncm
- 1x 10K Potentiometer 10 Turn
- 5x M3*20
- 4x M3*16
- 2x M2*20 + Nut
- 6x M4*10
- 4x M3*20 countersunk head

List of materials (inside electronics):

- Arduino UNO
- 1x power supply 12 V
- 1x jack connector for breadboard
- 1x Protobreadboard halfsized
- JST-connectors
- 1x 100uF electrolyte capacitor
- 1x stepper driver (e. g. A4988)
- 1x Adafruit MicroSD Card Breakout Board (with SPI) + micro SD (for Access control + data logging)
- 1x RTC Breakout Board Real Time Clock

  For wireless version:
  - radio component(NRF24L01)

List of materials (outside electronics):

- 4x M3*4
- 4x M4*6
- 1x jack connector for breadboard
- 1x power supply 12 V
- 1x pieco beeper (active)
- JST-connectors
- 1x 100uF electrolyte capacitor
- 1x button / led red, 3V, 10 mm
- 1x button / led green, 3V, 10 mm
- 1x PN532 NFC RFID Module
- 1x Protobreadboard halfsized
  
  For wireless version: 
  - Arduino Nano
  - radio component(NRF24L01)
   


