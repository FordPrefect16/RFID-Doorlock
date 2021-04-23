# RFID-Doorlock
A 3D-printable Doorlock which can attached at a standard door lock cylinder. Opens via RFID-Tag

Aim of this project is to create a electronic doorlock for access control and logging on an sd card. It shall be used on the door of our makerspace. 

The first version of this lock will rely on a wireconnection between outer and inner parts of the lock, hopefully later versions will communicate over radio. 
STL an CAD files can be found under main.

### Short description of planed functions

The mechanism at the inside of the door is shoved over the key and can be secured with two screws at the fittings and two additional screws. Also the cylinder is secured with a press fitting. When a RFID Tag is registered at the outer component, the tag will be compared to the entitled codes on a csv-file on sd. When access is granted, the buttons (which indicate the lockstate via LED - open or closed) can be pressed. The green one opens the lock, the red closes it. Tag an action will be logged on a csv-file. The lockstate is retrieved through a 10 turn potentiometer, to secure right Information, even if lockstate is changed to mechanical action. The lock can be manual overridden from inside by turning the wheel oder from outside with the right key for the cylinder. 
 
<img src="https://user-images.githubusercontent.com/77248262/115462890-7b3fbc00-a22b-11eb-9033-8d924fb0e1f9.jpg" alt="alt text" width="500" height="666,5">
<img src="https://user-images.githubusercontent.com/77248262/115464666-b5aa5880-a22d-11eb-8e3c-b19e01390406.jpg" alt="alt text" width="500" height="666,5">

# Materials used

Printed in black PLA on a Ender 3

### List of materials (inside mechanics):

- 1x cylinder with key used in door
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

### List of materials (controller/electronics):

- Arduino UNO <br>
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

### List of materials (door terminal):

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
   
### Mechanism without hull

<img src="https://user-images.githubusercontent.com/77248262/115464669-b6db8580-a22d-11eb-913c-e9444e7710ba.jpg" alt="alt text" width="500" height="990,5">


