/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 16 servos, one after the other

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
// Scanner detected 40 and 70
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
// These values give about 180 degrees
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  yield();
}

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  //Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  //Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  //Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void setServoAngle(double angle)
{
   // angle is from 0 to 180
  double pulse =  map(angle,0.0,180.0,SERVOMIN,SERVOMAX);
  pwm.setPWM(0, 0, pulse);
  delay(15);
}

void loop() {
  // Drive each servo one at a time
//  Serial.println(servonum);
  //for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen+=50) {
    //pwm.setPWM(servonum, 0, pulselen);
    //Serial.println(pulselen);
  //}

  // Single shot
  setServoAngle(180);

  //for (int angle = 0; angle < 180; angle+=60)
  //{
   // setServoAngle(angle);
  //}
  delay(500);
  for (int angle = 180; angle > 0; angle--)
  {
    setServoAngle(angle);
  }
  //for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
   // pwm.setPWM(servonum, 0, pulselen);
    //    //Serial.println(pulselen);
 // }

  delay(500);
  servonum = 0;
  //servonum ++;
  //if (servonum > 7) servonum = 0;
}
