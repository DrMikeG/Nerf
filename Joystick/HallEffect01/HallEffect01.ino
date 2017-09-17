/*
 * 
 * KY-003 Arduino
 * S Pin A3
 * middle  +5V
 * - GND
 * Magnet detection appears to be field line dependent (magnet and sensor need to be the correct way up...)
 */

int led = 13;//LED pin
int sensor = A3; //sensor pin
int val; //numeric variable

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT); //set LED pin as output
  pinMode(sensor, INPUT_PULLUP); //set sensor pin as input
}

void loop()
{
  val = analogRead(sensor); 
  
  if(val < 100) //when magnetic field is detected, turn led on
  {
    Serial.println("magnet!");   
  }
}
