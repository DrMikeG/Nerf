int ledPin = 5;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);    
  digitalWrite(ledPin, LOW);    // sets the LED off 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH);   // sets the LED on
  Serial.println("HIGH - OFF");
  delay(3000);                  // waits for a second
  digitalWrite(ledPin, LOW);    // sets the LED off
  Serial.println("LOW - ON");
  delay(3000);                  // waits for a second
}
