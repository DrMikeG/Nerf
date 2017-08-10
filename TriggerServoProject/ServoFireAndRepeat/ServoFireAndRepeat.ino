// This is attempting to print out the current being drawn - whilst the servo and motors are running.
// It's not quite working yet - it is constantly reading values in the 7000's.

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

int homeA = 65;
int fwdA = 0;

int phase;
unsigned long cycleStartTime;

volatile long isrCount;
volatile double average = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);     
  for (int i=0; i < 10; i++)
  {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay((11-i)*100);               // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay((11-i)*100);               // wait for a second
  }
  
  
  Serial.println("16 channel Servo test!");
  pinMode(pinOut, OUTPUT); 
  digitalWrite(pinOut, LOW);
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  
  phase = 0;
  cycleStartTime = 0;
  
  yield();
  
  average = 0.0;
  isrCount = 0;
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);

}

// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) 
{
  isrCount++;
  int sensorValue = analogRead(A7);
  float voltage = sensorValue * (5.0 / 1023.0);  
  average += voltage;

  printAvgVoltage();
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

double getMillamps(double sensorVoltage)
{
   double range =5.0;// amps
   double voltageSwing = 1.5;// volts
   double midVoltage = 2.5;
   return ((midVoltage - sensorVoltage)/voltageSwing) * range * 1000.0;
}


void printAvgVoltage()
{
  if (isrCount > 100)
  {
    // print out the value you read:
    double localAverage = average/(1.0*isrCount);
    double mA = getMillamps(localAverage);
    if (mA > 50.0)
    {
      Serial.print( mA  );
      Serial.print( ","  );
    }
    average = 0.0;
    isrCount = 0;
  }
}
  
  
void loop() {
  // Drive each servo one at a time
 
 if (phase == 0)
 {
   powerUpMotors();
   cycleStartTime = millis();
   Serial.println("Moving...");
   setServoAngle(homeA);  // Home
   Serial.println(homeA);
   phase = 1;
 }

 unsigned long time = millis() - cycleStartTime; // Time elapsed since start of cycle...
 
 if (time > 6000 && phase == 1) // first delay...
 {
   Serial.println("Moving...");
   setServoAngle(fwdA);  // Fire
   Serial.println("Moving...");
   Serial.println(fwdA);
   delay(800);
   phase = 2;
 }
 else if (time > 6000+800 && phase == 2)
 {
   Serial.println("Moving...");
   setServoAngle(homeA);  // Home   
   Serial.println(homeA);
   powerDownMotors();
   phase = 0;
 }


//  printAvgVoltage();
  //collectAndPrintVoltage();
  
  
}
