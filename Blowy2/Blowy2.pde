/*
  Blowy -- Now with amazing state change detection 
 	
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
 
 created  27 Sep 2005
 modified 14 Oct 2010
 by Tom Igoe
 
 This example code is in the public domain.
 	
 http://arduino.cc/en/Tutorial/ButtonStateChange
 
 */

// this constant won't change:
const int  buttonPin1 = 14;    // the pin that the pushbutton is attached to
const int  buttonPin2 = 15;    // the pin that the pushbutton is attached to
const int fanPin1 = 12;       // the pin that the LED is attached to
const int fanPin2 = 13;       // the pin that the LED is attached to
const unsigned long debounceDelay = 1000;    // the debounce time; increase if the output flickers
const unsigned long displayDelay = 30000;    // how much time must pass before the skirt goes into diplay mode.

// Variables will change:
int buttonPushCounter1 = 0;   // counter for the number of button presses
int buttonState1 = 0;         // current state of the button
int lastButtonState1 = 0;     // previous state of the button
int buttonPushCounter2 = 0;   // counter for the number of button presses
int buttonState2 = 0;         // current state of the button
int lastButtonState2 = 0;     // previous state of the button
int displayState = 0;         // current state of the button
int lastDisplayState = 0;     // previous state of the button
unsigned long lastDebounceTime1 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime2 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTimeD = 0;  // the last time the output pin was toggled

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  // initialize the LED as an output:
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

  // compare the buttonState to its previous state
  if ((buttonState1 != lastButtonState1) && ((millis() - lastDebounceTime1) > debounceDelay)) {
    // if the state has changed, increment the counter
    lastDebounceTime1 = millis();
    if (buttonState1 == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter1++;

      Serial.print("number of button 1 pushes:  ");
      Serial.println(buttonPushCounter1, DEC);
    }
  }
  if ((buttonState2 != lastButtonState2) && ((millis() - lastDebounceTime2) > debounceDelay)) {
    // if the state has changed, increment the counter
    lastDebounceTime2 = millis();

    if (buttonState2 == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter2++;

      Serial.print("number of button 2 pushes:  ");
      Serial.println(buttonPushCounter2, DEC);
    } 
    else {
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;


  // turns on the LED every four button pushes by 
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of 
  // the division of two numbers:

  if (((millis() - lastDebounceTime1) > displayDelay) || ((millis() - lastDebounceTime1) > displayDelay) ){//test the Display delay time.
    if ((millis() - lastDebounceTimeD) > displayDelay){
      lastDebounceTimeD = millis();
      buttonPushCounter1++;
    }
  }

  if (buttonPushCounter1 % 2 == 0) {
    digitalWrite(fanPin1, HIGH);
    digitalWrite(fanPin2, HIGH);
    //Serial.println("on");
  } 
  else {
    digitalWrite(fanPin1, LOW);
    digitalWrite(fanPin2, LOW);
    // Serial.println("off");
  }
}














