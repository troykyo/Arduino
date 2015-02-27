#include <SoftwareServo.h> 

SoftwareServo myservo;  // create servo object to control a servo 

int potpin = 0;  // analog pin used to connect the potentiometer
int serValue;    // variable to read the value from the analog pin 
int buttonState1 = 0;         // variable for reading the pushbutton status
const int buttonPin1 = 19;     // the number of the pushbutton pin
const int ledPin = 12;      // LED light

void setup() 

{ 
  Serial.begin(9600);
  myservo.attach(7);  // attaches the servo on pin 7 to the servo object 
} 

void loop() 
{  
  myservo.write(0);                  // sets the servo position according to the scaled value  
  buttonState1 = digitalRead(buttonPin1); //read the button state
  digitalWrite(ledPin, HIGH);  // turn LED on
  if (buttonState1 == HIGH){      // bail out on button sensor detect
      Serial.println("Begining Scan, Press start now.");
      digitalWrite(ledPin, LOW);  // turn LED off
      delay(7000);                           
      for(int serValue = 0 ; serValue <= 179; serValue +=1) {  // sets the value (range from 0 to 180):
      myservo.write(serValue);  // sets the servo position according to the scaled value 
      Serial.print (serValue);
      Serial.print (", ");
      delay(10); // waits for the servo to get there                             
      }
  Serial.println (serValue); 
  delay(15);                           

  SoftwareServo::refresh();
  } 
}
