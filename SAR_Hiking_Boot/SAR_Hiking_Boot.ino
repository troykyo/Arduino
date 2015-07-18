//RISD Summer School at SLEM, Troy Nachtigall and Dan

#include <Adafruit_NeoPixel.h>

#define PIN 1

int R = 0;
int G = 256;
int B = 0;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);


const int buttonPin = 2;    // the number of the pushbutton pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 200;    // the debounce time; increase if the output flickers
unsigned long emergencyTimer = 200;    // the debounce time; increase if the output flickers
int resetTime = 60 * 1000; //60 Seconds
int LED = 0;
int shortBlink = 100;
int longBlink = 1000;
unsigned long thisBlink = 0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 1:
  buttonCheck(); //See below
  // print out the value you read:
  if ((millis() - emergencyTimer) > resetTime) { //emergency Mode (More than one minute)
    thisBlink = millis();
    while ((millis() - thisBlink) < shortBlink) { //Fade up: time right now minus time we started is less than 1000
      R = map((millis() - thisBlink), 0, shortBlink, 0, 255);
      G = 0;
      B = 0;
      strip.setPixelColor(LED, strip.Color(R, G, B));
      strip.show();
      buttonCheck();
    }
    while ((millis() - thisBlink) < shortBlink * 2) {//Fade Down
      R = map((millis() - thisBlink), shortBlink, shortBlink * 2, 255, 0);
      G = 0;
      B = 0;
      strip.setPixelColor(LED, strip.Color(R, G, B));
      strip.show();
      buttonCheck();
    }
  }
  else {
    thisBlink = millis();
    while ((millis() - thisBlink) < longBlink) { //Fade up: time right now minus time we started is less than 1000
      R = 0;
      G = map((millis() - thisBlink), 0, longBlink, 0, 255);
      B = 0;
      strip.setPixelColor(LED, strip.Color(R, G, B));
      strip.show();
      buttonCheck();
    }
    while ((millis() - thisBlink) < longBlink * 2) {//Fade Down
      R = 0;
      G = map((millis() - thisBlink), longBlink, longBlink * 2, 255, 0);
      B = 0;
      strip.setPixelColor(LED, strip.Color(R, G, B));
      strip.show();
      buttonCheck();
    }
  }
}

void buttonCheck() {
  // If the switch changed, due to noise or pressing:
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        emergencyTimer = millis();
      }
    }
  }
}
