#include <Adafruit_NeoPixel.h>

#define PIN 1

int R = 0;
int G = 127;
int B = 255;
int brightness = 0;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by
int sensorValue = 0;
int stepValue = 0;
int maxBright = 0;
int minBright = 1024;
unsigned long counter = 0;
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setPixelColor(0, strip.Color(R, G, B));
  sensorValue = analogRead(A1);
  delay(1000);
}

// the loop routine runs over and over again forever:
void loop() {
  counter ++;
  if ((counter % 300000) == 0) {
    maxBright = 0;
    minBright = 1024;
  }
  // read the input on analog pin 1:
  sensorValue = analogRead(A1);
  if (sensorValue > maxBright) {
    maxBright = sensorValue;
  }
  if (sensorValue < minBright) {
    minBright = sensorValue;
  }

  stepValue = digitalRead(0);

  // print out the value you read:

  delay(1);        // delay in between reads for stability

  while (stepValue == 0) {
   rainbowCycle(10); 
   }
  R = R + fadeAmount;
  B = B + fadeAmount;
  // reverse the direction of the fading at the ends of the fade:
  if (R <= 0 || R >= 255) {
    fadeAmount = -fadeAmount;
    for (int i = 0; i<8; i++){
    strip.setPixelColor(i, strip.Color(R, G, B));
    strip.show();
    }
  }
}
  void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + counter) & 255));
   
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

