/*
Finnge s
 
 */

// this constant won't change:
const int  fringePin1 = 2;    // the pin that the pushfringe is attached to
const int  fringePin2 = 3;    // the pin that the pushfringe is attached to
const int  fringePin3 = 4;    // the pin that the pushfringe is attached to
const int  fringePin4 = 9;    // the pin that the pushfringe is attached to
const int  fringePin5 = 10;    // the pin that the pushfringe is attached to
const int  fringePin6 = 11;    // the pin that the pushfringe is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int fringePushCounter = 0;   // counter for the number of fringe presses
int fringeState1 = 0;         // current state of the fringe
int fringeState2 = 0;         // current state of the fringe
int fringeState3 = 0;         // current state of the fringe
int fringeState4 = 0;         // current state of the fringe
int fringeState5 = 0;         // current state of the fringe
int fringeState6 = 0;         // current state of the fringe
int lastfringeState1 = 0;     // previous state of the fringe
int lastfringeState2 = 0;     // previous state of the fringe
int lastfringeState3 = 0;     // previous state of the fringe
int lastfringeState4 = 0;     // previous state of the fringe
int lastfringeState5 = 0;     // previous state of the fringe
int lastfringeState6 = 0;     // previous state of the fringe

void setup() {
  // initialize the fringe pin as a input:
  pinMode(fringePin1, INPUT);
  pinMode(fringePin2, INPUT);
  pinMode(fringePin3, INPUT);
  pinMode(fringePin4, INPUT);
  pinMode(fringePin5, INPUT);
  pinMode(fringePin6, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the pushfringe input pin:
  fringeState1 = digitalRead(fringePin1);
  fringeState2 = digitalRead(fringePin2);
  fringeState3 = digitalRead(fringePin3);
  fringeState4 = digitalRead(fringePin4);
  fringeState5 = digitalRead(fringePin5);
  fringeState6 = digitalRead(fringePin6);

  // compare the fringeState to its previous state
  if (fringeState != lastfringeState) {
    // if the state has changed, increment the counter   
      fringePushCounter++;

      Serial.println(fringePushCounter, DEC);
    } 
    else {
      // if the current state is LOW then the fringe
      // wend from on to off:
      Serial.println("off"); 
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastfringeState1 = fringeState1;
  lastfringeState2 = fringeState2;
  lastfringeState3 = fringeState3;
  lastfringeState4 = fringeState4;
  lastfringeState5 = fringeState5;
  lastfringeState6 = fringeState6;
  
  // turns on the LED every four fringe pushes by 
  // checking the modulo of the fringe push counter.
  // the modulo function gives you the remainder of 
  // the division of two numbers:
  if (fringePushCounter % 4 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
   digitalWrite(ledPin, LOW);
  }
  
}









