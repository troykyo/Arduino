// Slem Sole Workshop Sketch
// released under the GPLv3 license 

// Hookup Pro Trinket : Neopixel
// GND :  -
// 5V  :  +
// 6   :  -> (in)

//Sensor Hookup
//10k Resistors from GND to A1, A3, A5
//Eyonix sensor from 5V to A1, A3, A5

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 15; // delay for half a second is 500
int g = 0; // start green
int r = 0;  // start red
int b = 255;  // start blue
int sensorBlue = A1;
int sensorGreen = A3;
int sensorRed = A5;
int sensorReadingBlue = 0;
int sensorReadingGreen = 0;
int sensorReadingRed = 0;

void setup() {
 // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
 if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
 // End of trinket special code
 pinMode(sensorBlue, INPUT);
 pinMode(sensorGreen, INPUT);
 pinMode(sensorRed, INPUT);

 pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

 // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

 sensorReadingBlue = analogRead(sensorBlue);
 sensorReadingGreen = analogRead(sensorGreen);
 sensorReadingRed = analogRead(sensorRed);
 b = map(sensorReadingBlue, 0, 1023, 255, 0);
 g = map(sensorReadingGreen, 0, 1023, 255, 0);
 r = map(sensorReadingRed, 0, 1023, 255, 0);



 // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
 pixels.setPixelColor(0, pixels.Color(r, g, b)); // Pressure mix.

 pixels.show(); // This sends the updated pixel color to the hardware.
}
