
//

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

int loopLength = 750;

double getMillamps(double sensorVoltage)
{
   double range =5.0;// amps
   double voltageSwing = 1.5;// volts
   double midVoltage = 2.5;
   return ((midVoltage - sensorVoltage)/voltageSwing) * range * 1000.0;
}

// the loop routine runs over and over again forever:
void loop() {

  
  double average = 0.0;
  for (int i=0; i < loopLength; i++)
  {
    int sensorValue = analogRead(A5);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage = sensorValue * (5.0 / 1023.0);  
    average += voltage;
  }
  
  // print out the value you read:
  average = average/(1.0*loopLength);
  double mA = getMillamps(average);
  if (mA > 50.0)
  {
    Serial.print( mA  );
    Serial.print( ","  );
  }
}
