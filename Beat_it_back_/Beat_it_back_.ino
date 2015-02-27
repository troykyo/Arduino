/*
 One Button Synth

 Beat it back on a seven light neopixel

 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin
const int playbackDelay = 3000  //the number of milliseconds needed before the program starts
                          // Variables will change:
                          int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int beats[100] = { //100 beats of love
};
int whichBeat = 0; //array pointer
int playmode = 1;  //state change for play vs Rec mode.
int thisBeat = 0; //Current play back beat.

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 100;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      if (playmode == 1) {
        whichbeat = 0; //reset the beat index
      }
      playmode = 0;
      buttonState = reading;
      beats[whichBeat] = millis(); //the time the beat happened.
      whichBeat++; //move to the next beat
      // only toggle the LED if the new button state is HIGH
      lightOff():
        if (buttonState == HIGH) {
        lightOn();
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;

  if ((millis () - beats[whichBeat]) > playbackDelay) && (playmode == 0) {
    / //Playback mode timeout
    playmode == 1;
    beatSync =  beats[(whichBeat - 1)] - beats[0]//How long is a beat sequence
    if (beatSync < playbackdelay) {//reset the beat sequence time to synchronize with the music
      if (beatSync * 2 < playbackDelay) {
        if (beatSync * 3 < playbackDelay) {
          beatSync = beatSync * 4;
        }
        else {
          beatSync = beatSync * 3;
        }
      }
      else {
        beatSync = beatSync * 2;
      }
    }
    beats[whichbeat] = 0; //delete the last tap as its is a stop indicator
    beats[(whichbeat - 1)] = 0; //This also provides a stopping point if there is more data in the array
    lightOn(); //always turn the light on for the first beat
    startTime = millis();//remeber when we started blinking
    playmode = 1;
  }
  if (millis() > (startTime + beatsync)  {
  thisBeat++;
  if beats(thisBeat) == 0{
      thisBeat = 0;
      startTime = millis();//remeber when we started blinking
      playmode = 1;
      lightOn(); //always turn the light on f or the first beat
    }
    if (thisBeat % 2 == 0) {
      lightOn();
    }
    else {
      lightOff();
    }
  }
}
}
