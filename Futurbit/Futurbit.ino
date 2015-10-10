#include <Adafruit_NeoPixel.h>

#define PIN 6

int R = 0;
int G = 0;
int B = 0;
int bright = 0;
int counter = 0;
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  color();
  for (bright = 0; bright <= 255; bright++) {
    R = bright;
    G = bright;
    color();
    delay(1);
  }
}

// the loop routine runs over and over again forever:
void loop() {

  for (bright = 255; bright >= 0; bright--) {
    R = bright;
    if (bright < 40) {
      B = abs(bright-40);
    }
    color();
    delay(5);
  }
  /*
  for (bright = 0; bright <= 25; bright++) {
    B = bright;
    color();
  }

  for (bright = 25; bright >= 0; bright--) {
    B = bright;
    color();
  }*/
  delay (3000);
  for (bright = 0; bright <= 255; bright++) {
    R = bright;
    if (bright < 40) {
      B = abs(bright-40);
    }
    color();
    delay(5);
  }
  Serial.println (counter);
  delay (3000);
}
void color() {
  for (int LED = 0; LED <= 16; LED++) {
    strip.setPixelColor(LED, strip.Color(R, G, B));
    strip.show();
    delay(0);        // delay for stability
    Serial.print (R);
    Serial.print (" ");
    Serial.print (G);
    Serial.print (" ");
    Serial.println (B);
  }
}
