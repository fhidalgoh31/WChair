#include <SoftwareSerial.h>
#include "MAX6955_i2c.h"
#include "I2C.h"
#include <Wire.h>

#define JOY_FR1 A0
#define JOY_FR2 A1
#define JOY_LR1 A2
#define JOY_LR2 A3
#define JOY_CNTR A7

SoftwareSerial mySerial(13, 12); // RX, TX

int MAX6955::write_print(char command, char data){    // test only delete ZZZ change to write
    int i;
    while (1)
    {
        int j=I2c.write(_id,command,data);
        mySerial.print("write return: "); mySerial.println(j);
        i++;
        if (j==0)
            break;
        delay(100);
    }
    return i;
}


int MAX6955::write_check(char command, char data){
    mySerial.print("w_attempt: ");mySerial.println(I2c.write(_id,command,data));
    // read_check(command);
}

int MAX6955::read_check(char command){
    byte read_byte;
    int i=0;
    while (!I2c.available())
      {
        read_byte=read(command);
        i++;
        if (i==1000)
          break;
      }
      mySerial.print("r_attempt: ");mySerial.print(i); mySerial.print(" ISP 0X");mySerial.print(command,HEX);mySerial.print(" : ");mySerial.println(read_byte,HEX);
}

class Joystick
{
  private:
    char joy_analog[5]={JOY_FR1,JOY_FR2,JOY_LR1,JOY_LR2,JOY_CNTR};
    int joy_values[5];

      // 1: valid data   ,   0: error
    int read_joy()
    {
      for (int i=0;i<5;i++)
      {
        int val = analogRead(joy_analog[i]);  // read the input pin
        delay(10);
        val = analogRead(joy_analog[i]);  // read the input pin
        delay(10);
        joy_values[i]=val;
      }
      // validate data
      if ((fr1() + fr2() > 900) && (lr1() + lr2() > 900) && (cntr()>450) && (cntr()<550))
        return 1;
      else
        return 0;
    }

  public:
  // return values:
    int fr1()
      {return joy_values[0];}
    int fr2()
    {return joy_values[1];}
    int lr1()
      {return joy_values[2];}
    int lr2()
      {return joy_values[3];}
    int cntr()
      {return joy_values[4];}

    void print_all()
    {
      for (int i=0;i<5;i++)
      {
      mySerial.print(i); mySerial.print(": "); mySerial.println(joy_values[i]);          // debug value
      }
    }
    void scaled_values()
    {
      if (read_joy())
      {
        mySerial.print("L/R: "); mySerial.println(map(fr1(),0,1024,-1000,1000));          // debug value
        mySerial.print("F/R: "); mySerial.println(map(lr1(),0,1024,-1000,1000));          // debug value
        mySerial.println("");
        Serial.print("!VAR 17 ");Serial.println(map(fr1(),0,1024,-1000,1000));
        Serial.print("!VAR 18 ");Serial.println(map(lr1(),0,1024,-1000,1000));
      }
    }
};

MAX6955 leds(0B1100000);

void setup() {
  // set the data rate for the SoftwareSerial port
  Serial.begin(115200);
  mySerial.begin(115200);
  mySerial.println("Hello, world?");

   
  // I2c.setSpeed(3400000);
    I2c.timeOut(80);
    I2c.begin();
    // leds.write_print(max6955_reg_decodeMode,0xFF);  //no decode
    // leds.write_print(max6955_reg_globalIntensity,0x07);
    // leds.write_print(max6955_reg_scanLimit,0x05);
    // leds.write_print(max6955_reg_configuration,0x01);
    // leds.write_print(max6955_reg_portConfiguration,0B01011000);   // scan o0,o1, input p0,p1
    // leds.write_print(max6955_reg_digitType,0x00);
    // leds.write_print(max6955_reg_displayTest,0x00);
  leds.init();

  // for (int i=0; i<100; i++)
    // leds.write_check(max6955_reg_configuration,0x00);   // shutdown mode

  delay(2000);
  // leds.write_print(max6955_reg_displayTest,0x0);
  // for (int i=0; i<100; i++)
    // leds.write_check(max6955_reg_configuration,0x01);   // normal mode
  
  // delay(2000);
  // leds.write(max6955_reg_digit3, 0xFF); // all 1!
  // leds.write(max6955_reg_digit4, 0xFF); // all 1!
  // leds.write(max6955_reg_digit5, 0xFF); // all 1!
    Wire.begin();  //init wire
}

void loop() { // run over and over
  static Joystick joy;
  static int i=0;

  leds.write_print(max6955_reg_digit3,0x55);
  i++;
  mySerial.print("loop:");mySerial.println(i);
  delay(1000);
asdf: goto asdf;
  leds.write_print(max6955_reg_digit3,0xAA);
  i++;
  mySerial.print("loop:");mySerial.println(i);
  delay(1000);
  return;

 
  mySerial.println("ini");
  Wire.beginTransmission(0B11000000); //escribir
  Wire.write(max6955_reg_digit3);
  Wire.write(0xAA);
  Wire.endTransmission();     // stop transmitting
  mySerial.println("fin");
return;


  joy.scaled_values();
  // leds.write(max6955_reg_digit3, i); // all 1!
  // leds.write(max6955_reg_digit4, i); // all 1!
  // leds.write(max6955_reg_digit5, i); // all 1!
  // leds.write(max6955_reg_digit3a, i); // all 1!
  // leds.write(max6955_reg_digit4a, i); // all 1!
  i++;

  // leds.read_check(0x08);
  // leds.write(0x08, 0xFF); // read key_a
  // mySerial.print("read: "); mySerial.println(leds.read(0x0C),BIN);

  delay(500);
}