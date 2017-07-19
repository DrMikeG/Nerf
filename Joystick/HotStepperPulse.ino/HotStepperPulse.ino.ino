// Shows how to run three Steppers at once with varying speeds
//
// Requires the Adafruit_Motorshield v2 library 
//   https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
// And AccelStepper with AFMotor support 
//   https://github.com/adafruit/AccelStepper

// This tutorial is for Adafruit Motorshield v2 only!
// Will not work with v1 shields

#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

const int STEPSPERREV = 1025;
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

// Connect two steppers with 200 steps per revolution (1.8 degree)
// to the top shield
Adafruit_StepperMotor *myStepper1 = AFMStop.getStepper(STEPSPERREV, 1);
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(STEPSPERREV, 2);

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {  
  myStepper1->onestep(FORWARD, DOUBLE);
}
void backwardstep1() {  
  myStepper1->onestep(BACKWARD, DOUBLE);
}
// wrappers for the second motor!
void forwardstep2() {  
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {  
  myStepper2->onestep(BACKWARD, DOUBLE);
}
// Now we'll wrap the 3 steppers in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);


void setup()
{  
    // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

delay(1000);

// What would 10 RPM be?


float speed1 =-88; // steps per second - motor 1
float speed2 =162; // steps per second - motor 2

float rpm1 = (60.0 * speed1) / STEPSPERREV;
float rpm2 = (60.0 * speed2) / STEPSPERREV;
Serial.print("rpm motor 1 = ");
Serial.println(rpm1);
Serial.print("rpm motor 2 = ");
Serial.println(rpm2);  
AFMStop.begin(); // Start the top shield
stepper1.setSpeed(speed1);
stepper2.setSpeed(speed2);
  
}

void loop()
{
    stepper1.runSpeed();
    stepper2.runSpeed();   

}

