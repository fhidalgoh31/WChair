//https://forum.arduino.cc/index.php?topic=389637.0


#include <Wire.h>

byte debounced;  //Indicates which switches were detected and debounced by the MAX6959
byte pressed;   //Indicates which switches were detected as pressed by the MAX6959 

void setup() {
 //Open the serial port
 Serial.begin(9600);
 
 //Initialize the MAX6959 operating state
 Wire.begin();
 Wire.beginTransmission(0x38);
 Wire.write(0x01); // sets starting address to decode mode register
 Wire.write(0x0F); // reg 0xo1 - enable decode mode for all digits
 Wire.write(0x20); // reg 0x02 - half intensity 
 Wire.write(0x03); // reg 0x03 - scan limit 3
 Wire.write(0x03); // reg 0x04 - normal operation
 // Writing to register 0x05 is forbidden so this must be ended here
 Wire.endTransmission();
 Wire.beginTransmission(0x38);
 Wire.write(0x06); // sets starting address to GPIO register
 Wire.write(0x98); /* reg 0x06 - IRQ/SEG9 is segment driver and
 Input1 and Input2 are set to keyscan */  
 Wire.endTransmission();

}

void loop() {
 //Read the switches connected to the MAX6959 Input1 and Input2 pins
 
 //Set MAX register address to debounced keys
 Wire.beginTransmission(0x38); //Slave address
 Wire.write(0x08); //Debounced key register address
 Wire.endTransmission();
 
 //Read starting at the the debounced key register
 Wire.requestFrom(0x38, 4);
 while(Wire.available())
 {
   debounced = Wire.read();
   Serial.println(debounced,BIN);
 }