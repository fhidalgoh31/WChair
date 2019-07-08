#include <SoftwareSerial.h>
#include <Wire.h>
#include "MAX6955.h"



#define JOY_FR1 A0
#define JOY_FR2 A1
#define JOY_LR1 A2
#define JOY_LR2 A3
#define JOY_CNTR A7

SoftwareSerial mySerial(13, 12); // RX, TX
MAX6955 leds(0B11000000);

void setup() {
  // set the data rate for the SoftwareSerial port
  Serial.begin(115200);
  mySerial.begin(115200);
 
  mySerial.println("Hello,  2??????");

 delay(10);
 leds.init();
 
}

void loop() { // run over and over
  
  // delay(2000);
  // Wire.beginTransmission(SLA_W(0B11000000));
  // leds.write(max6955_reg_digit3, 0x55); // no decode!
  
  // delay(2000);
  //  Wire.beginTransmission(SLA_W(0B11000000));
  // leds.write(max6955_reg_digit3, 0xAA); // no decode!

  
  delay(500);
}