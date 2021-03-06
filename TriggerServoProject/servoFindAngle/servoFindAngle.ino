#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
// Scanner detected 40 and 70
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

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

int homeA = 65;
int fwdA = 0;

volatile long isrCount;


void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pinMode(pinOut, OUTPUT); 
  digitalWrite(pinOut, LOW);
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  yield();

  isrCount = 0;
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);

}

 

// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) 
{
  isrCount++;
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
  Serial.println(pulse);
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

void CountDown25()
{
  for (int i=8; i > 0; i--){
    Serial.println(i);
    delay(1000);    
  }
}

  
void loop() {
 
 // What is connected to what?
// Adafruit_PWMServoDriver - uses A4/A5/GND/5V

// I think it's expecting a servo on pin 15 of the servo board.
// Can we reach angle 0 - SERVOMIN = 120


//setServoAngle(65); // This is a good home value 258
pwm.setPWM(0, 0, 258);
CountDown25();
Serial.println("Fire!");
//pwm.setPWM(0, 0, 125); // This seems to be about the minimum where the dart gets cleanly picked up
delay(500);



// setServoAngle(0); - No! Too far!

/* 
  // Drive each servo one at a time
 Serial.println(isrCount);
 powerUpMotors();
 setServoAngle(homeA);  // Home
 Serial.println(homeA);
 delay(5000);
 setServoAngle(fwdA);  // Fire
 Serial.println(fwdA);
 delay(800);
 setServoAngle(homeA);  // Home
 powerDownMotors();
 */
  
}
