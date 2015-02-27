/*
  Button Count
 
 Counts how many times a button has be pressed a prints it to Serial.   
 Great for understanding why a a button needs debounded.
 
 The circuit:
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 created March, 2010
 by troykyo

 This example code is in the public domain.
 Based upon the original button code by Tom Igoe
 */

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int previousState = 0;       // state change detection if the button was pressed before
int touchCounter = 0; // counter for how many times the button has been touched

void setup() {
  Serial.begin(9600); 
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed and was not pressed before.
  // if it is and was not pressed before, the buttonState is HIGH 
  //and a touch is sento to serial:
  if ((buttonState == HIGH) && (previousState == 0))  {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH); 
    touchCounter++;
    Serial.print(touchCounter);
    previousState == 1; //State Change detected
  } 
  else if((buttonState == LOW) && (previousState == 1)) {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
    previousState == 0; //State Change detected
  }
}
