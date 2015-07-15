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

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 1:
  int sensorValue = analogRead(A1);
  // print out the value you read:
  delay(30);        // delay in between reads for stability
  R = map(sensorValue, 0, 1023, 0, 255);
  for (int LED = 0; LED <= 16; LED++) {
    strip.setPixelColor(LED, strip.Color(R, G, B));
    strip.show();
  }
}
