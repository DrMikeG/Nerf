 int ledPin = 13;
 int joyPin1 = 0;                 // slider variable connecetd to analog pin 0
 int joyPin2 = 1;                 // slider variable connecetd to analog pin 1
 int switchPin = A2;              // Switch pin pulled high (shorts to ground when pressed)
 int value1 = 0;                  // variable to read the value from the analog pin 0
 int value2 = 0;                  // variable to read the value from the analog pin 1

 void setup() {
  pinMode(ledPin, OUTPUT);              // initializes digital pins 0 to 7 as outputs
  pinMode(joyPin1, INPUT);
  pinMode(joyPin2, INPUT);
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(9600);
 }


 void printDirection(int data1, int data2)
 {
   // Values go from 
   // data1 0 - 500 South
   // data1 530 - 1024 North
   // data2 0 - 500 West
   // data2 530 - 1024 East
   
   if (data1 > 500 && data1 < 530 &&
       data2 > 500 && data2 < 530)
       {
         Serial.println("DeadZone");
       }
       else
       {
         // There is at least one direction...
         if (data1 < 500)
         {
           Serial.print('S');
         }
         else if (data1 > 530)
         {
           Serial.print('N');
         }
         if (data2 < 500)
         {
           Serial.println('W');
         }
         else if (data2 > 530)
         {
           Serial.println('E');
         }
       }
 }
 
 void loop() {
  // reads the value of the variable resistor 
  value1 = analogRead(joyPin1);   
  // this small pause is needed between reading
  // analog pins, otherwise we get the same value twice
  delay(100);			  
  // reads the value of the variable resistor 
  value2 = analogRead(joyPin2);   

  printDirection(value1,value2);
  
  int buttonValue = digitalRead(switchPin);   // read the input pin  
  if (buttonValue == LOW)
  {
    Serial.println("Button pressed");
  }
  delay(100);		
  

 }
