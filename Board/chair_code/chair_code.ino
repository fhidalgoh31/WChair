#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11


char incomingByte = 0;    // for incoming serial data
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
void setup() {
  Serial.begin(115200);    // opens serial port, sets data rate to 9600 bps
  Serial.println('Test\n');
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(115200);
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
  
    // read the incoming byte:
    incomingByte = Serial.read();
  
    // say what you got:
    mySerial.print(incomingByte);
  }
  
    if (mySerial.available() > 0) {
  
    // read the incoming byte:
    incomingByte = mySerial.read();
  
    // say what you got:
    Serial.print(incomingByte);
  }
}