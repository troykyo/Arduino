/*
  Simple Thermostat 
 	
 Often, you don't need to know the state of a digital input all the time,
 but you just need to know when the input changes from one state to another.
 For example, you want to know when a button goes from OFF to ON.  This is called
 state change detection, or edge detection.
 
 This example shows how to detect when a button or button changes from off to on
 and on to off.
 	
 The circuit:
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 * LED attached from pin 13 to ground (or use the built-in LED on
 most Arduino boards)
 * 24V Relay attached to pin 7. 
 */

// this constant won't change:
const int buttonPin = 7;    // the pin that the pushbutton is attached to
const int ledPin = 14;      // the pin that the LED is attached to
const int caldaia = 3;      // the Pin that the relay is attached too.

// Variables will change:
int buttonPushCounter = 1;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
unsigned long buttonTimer = 0;
unsigned long lastButtonTime = 0;
unsigned long manualHeatTime = 60*1000; //30 minutes

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
    pinMode(caldaia , OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
  Serial.println("We are ready to rock.");
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
  buttonTimer = millis();

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    lastButtonTime = millis();
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      Serial.print("on ");
      Serial.println(buttonPushCounter, DEC);
    }   else {
      // if the current state is LOW then the button
      // wend from on to off:
      Serial.print("off "); 
      Serial.println(buttonPushCounter, DEC);
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState = buttonState;

  // turns on the LED every two button pushes by 
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of 
  // the division of two numbers:
 // if (abs(buttonTimer-lastButtonTime)>manualHeatTime) {
   // buttonPushCounter = 1; 
  //}
  if (buttonPushCounter % 2 == 0) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(caldaia, HIGH);
  } 
  else {
    digitalWrite(ledPin, LOW);
    digitalWrite(caldaia, LOW);
  }

}











