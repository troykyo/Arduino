const int ledPin1 = 2; 
const int ledPin2 = 13; 
const int ledPin3 = 0; 
const int ledPin4 = 1; 
const int ledPin5 = 3; 
const int ledPin6 = 4;
const int ledPin7 = 5; 
const int ledPin8 = 6; 
const int ledPin9 = 7; 
const int ledPin10 = 8; 
const int ledPin11 = 9; 
const int ledPin12 = 10; 
const int ledPin13 = 11; 
const int ledPin14 = 12; 
 
void setup() {
}  

void loop () {
Serial.begin(9600); // serial comm, data rate: 9600 bps
Serial.println("Begin");
digitalWrite(ledPin1, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin1, LOW);  // turn LED off
digitalWrite(ledPin2, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin2, LOW);  // turn LED off
digitalWrite(ledPin3, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin3, LOW);  // turn LED off
digitalWrite(ledPin4, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin4, LOW);  // turn LED off
digitalWrite(ledPin5, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin5, LOW);  // turn LED off
digitalWrite(ledPin6, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin6, LOW);  // turn LED off
digitalWrite(ledPin7, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin7, LOW);  // turn LED off
digitalWrite(ledPin8, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin8, LOW);  // turn LED off
digitalWrite(ledPin9, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin9, LOW);  // turn LED off
digitalWrite(ledPin10, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin10, LOW);  // turn LED off
digitalWrite(ledPin11, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin11, LOW);  // turn LED off
digitalWrite(ledPin12, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin12, LOW);  // turn LED off
digitalWrite(ledPin13, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin13, LOW);  // turn LED off
digitalWrite(ledPin14, HIGH);  // turn LED on
delay (500);
digitalWrite(ledPin14, LOW);  // turn LED off
}
