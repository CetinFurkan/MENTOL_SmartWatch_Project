#include <Wire.h>

unsigned char ALS_mode=0;
unsigned int lux=0;

void I2C_write(unsigned char add,unsigned char reg,unsigned char data) {
  Wire.beginTransmission(add);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission(1);  
}

void setup()
{
  ////////IO Init
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output

  ///////Sensor Init
  Wire.beginTransmission(0x39);
  Wire.write(0x00);
  Wire.write(0xd0);
  Wire.write(0x25);
  Wire.write(0x40);
  Wire.write(0x80);
  Wire.endTransmission(1);
}

void loop()
{
  ////Getting Light Data from Sensor
  unsigned short AD0=0,AD1=0;
  Wire.beginTransmission(0x39);
  Wire.write(0x0c);
  Wire.endTransmission(0);
  Wire.requestFrom(0x39, 4);    // request 4 bytes from slave device

  unsigned char i=0;
  while(Wire.available())
  { 
    unsigned char c = Wire.read(); // receive a byte as character
    switch (i) {
    case 0:
      AD0=c;
      break;  
    case 1:
      AD0+=(((unsigned short)c)<<8);
      break; 
    case 2:
      AD1=c;
      break; 
    case 3:
      AD1+=(((unsigned short)c)<<8);
      break; 
    }
    i++;
  }

  //// Calculation & get light results ////
  if (ALS_mode==0) {
    if (AD0>16000) {
      ALS_mode=1;
      I2C_write(0x39,0x00,0x0c);
      I2C_write(0x39,0x01,0x27);
      I2C_write(0x39,0x00,0xcc);
    }
    else {
      float ratio=(float)AD1/(float)AD0;
      if (ratio<0.67) {
        lux=(unsigned int)((6.650*(float)AD0)-(9.653*(float)AD1));
      }
      else {
        if (ratio>0.9) {
          lux=0;
        } 
        else {
          lux = (unsigned int)((1.805*(float)AD0)-(1.977*(float)AD1));
        } 
      }
    } 
  }
  else {
    if (AD0<1000) {
      ALS_mode=0;
      I2C_write(0x39,0x00,0x0c);
      I2C_write(0x39,0x01,0x25);
      I2C_write(0x39,0x00,0xcc);
    }
    else {
      float ratio=(float)AD1/(float)AD0;
      if (ratio<=0.67) {
        lux=4*(unsigned int)((6.650*(float)AD0)-(9.653*(float)AD1));
      }
      else {
        if (ratio>0.9) {
          lux=0;
        } 
        else {
          lux = 4*(unsigned int)((1.805*(float)AD0)-(1.977*(float)AD1));
        } 
      }
    } 
  }


  //////Display Result
  //////Use Serial Monitor with baudrate 115200 can read the result, the result is also displayed by the Leds cross
  //////User may modify codes below
  Serial.print("Lux : "); 
  Serial.println(lux,DEC);

  delay(200);
}










































