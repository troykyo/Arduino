/*
 One Button Synth

 Beat it back on a seven light neopixel

 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 9;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin
const int playbackDelay = 3000;  //the number of milliseconds needed before the program starts
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState = LOW;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int beats[100] = { //100 beats of love
};
int whichBeat = 0; //array pointer
int playmode = 1;  //state change for play vs Rec mode.
int thisBeat = 0; //Current play back beat.
int beatSync = 0;
int startTime = 0;

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 100;    // the debounce time; increase if the output flickers

#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  strip.begin(); // Start neopixels
  strip.show(); // Initialize all pixels to 'off'
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);  // set initial LED state
  digitalWrite(buttonPin, HIGH); //Pullup with an internal resistor.
  Serial.begin (9600);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  //if (reading > 0){
  //reading = 1;
  //}
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    Serial.print ("+");
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    Serial.println(" BOUNCE!");
    // if the button state has changed:
    if (reading != buttonState) {
      if (playmode == 1) {
          Serial.print("Array Reset ");
        whichBeat = 0; //reset the beat index
      }
      
      playmode = 0;
      buttonState = reading;
      beats[whichBeat] = millis(); //the time the beat happened.
      whichBeat++; //move to the next beat
      // only toggle the LED if the new button state is HIGH
      lightOff();
      if (buttonState == HIGH) {
        Serial.print("*");
        lightOn();
      }
    }
  }
  lastButtonState = reading;

  if (((millis () - beats[whichBeat]) > playbackDelay) && (playmode == 0)) {
    //Playback mode timeout
    playmode == 1;
    beatSync = beats[(whichBeat - 1)] - beats[0];//How long is a beat sequence
    if (beatSync < playbackDelay) {//reset the beat sequence time to synchronize with the music
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

    beats[whichBeat] = 0; //delete the last tap as its is a stop indicator
    beats[whichBeat - 1] = 0; //This also provides a stopping point if there is more data in the array
    lightOn(); //always turn the light on for the first beat
    startTime = millis();//remeber when we started blinking
    playmode = 1;
  }
  if (millis() > (startTime + beatSync))  {
    thisBeat++;
    if (beats[thisBeat] == 0) {
      for (int i = 0; i < thisBeat; i++) {
        Serial.print (beats[i]);
        Serial.print (", ");
        thisBeat = 0;
      }

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

void lightOn() {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED ON");
  /* for(uint16_t i=0; i<strip.numPixels(); i++) {
     strip.setPixelColor(i, strip.Color(0, 255, 0));
     strip.show();
     delay(0);
   }*/
}

void lightOff() {
  digitalWrite(ledPin, LOW);
  Serial.println("LED OFF");
  //strip.show(); // Initialize all pixels to 'off'
}


