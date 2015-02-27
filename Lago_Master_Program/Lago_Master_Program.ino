/*
Wearable Technology @ Lago #SalonediMobile2013

Troy Nachtigall and Make Tank

Attach the pillow prototye to pin 8 and 7
Attach the Bowl Prototipe to Pin 13 and A0

 */
#include "pitches.h"
// set pin numbers:
const int buttonPin = 7;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int buttonPinA = A0;     // the number of the pushbutton pin

// variables will change:
int buttonStateA = 0;         // variable for reading the pushbutton status
int buttonMedio = 0;         // variable for reading the pushbutton status

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
//  pinMode(ledPinA, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPinA, INPUT);    
  digitalWrite(buttonPinA, HIGH);    
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);  
  digitalWrite (buttonPin,HIGH);
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {
 
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  

    for (int thisNote = 0; thisNote < 8; thisNote++) {

      // to calculate the note duration, take one second 
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000/noteDurations[thisNote];
      tone(8, melody[thisNote],noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(8);
    }
  }
  else {
   for (int x = 0; x < 8; x++) {

    buttonStateA = analogRead(buttonPinA);
    buttonMedio = buttonMedio+buttonStateA;
  }
  buttonMedio= buttonMedio/8;
  Serial.println(buttonMedio);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonMedio < 950) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
  buttonMedio = 0;
  delay(10);
  }
 
}


