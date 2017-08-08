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
#define SERVOMIN  120 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  504 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;
int pinOut = 8;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pinMode(pinOut, OUTPUT); 
  digitalWrite(pinOut, LOW);
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

void powerUpMotors()
{
  Serial.println("Motors ON!");
  pwm.setPWM(15, 0, 4095);
  digitalWrite(pinOut, HIGH);
  delay(2000);

}

void powerDownMotors()
{
  Serial.println("Motors OFF!");
  digitalWrite(pinOut, LOW);
  pwm.setPWM(15, 0, 0);
}


void loop() {
  // Drive each servo one at a time
 
  powerUpMotors();

  
  Serial.println("Home!");  
  setServoAngle(50);
  
  // Because of the orientation of the servo, the throw is negative in angle.
  // If the throw is 50 degrees,
  // then we should start the servo at 50, and move it to 0 to fire.
  // This is a pain.
  
  delay(1500);
  powerDownMotors();
  delay(1500);
  
  
}
