/* 
 Troy Nachtigall and Jackie SLEM 2015 


*/

#include <Adafruit_NeoPixel.h>

#define PIN 1
int R = 0;
int G = 0;
int B = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

int numberOfStrokes = 5;//max 30
unsigned long StrokeTimeArray[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };;
int velostatSensor = 0;
unsigned long averageStroke = 0;
unsigned long lastStroke = 0;
unsigned long thisStroke = 0;
unsigned long timeStroke = 0;
unsigned long space = 0;//used for making an aware delay
unsigned long sensorDebounce = 0;//used for making an aware delay
int debounceDelay = 200;
int StrokeCounter = 0;
int VELOSENS = A1;

void setup() {
  pinMode(VELOSENS, INPUT); // Set Trinket/Gemma Digital 0 to output
  // to drive the piezo buzzer (important)
}

void loop() {
  averageStroke = 0; //reset the average
  sensorRead(); //read the sensor
  for (int j = 0; j < numberOfStrokes; j++) {
    averageStroke = averageStroke + (StrokeTimeArray[(j + 1)] - StrokeTimeArray[(j)]); //add all the Stroke times together
  }
  averageStroke = averageStroke / numberOfStrokes; //calculate the average
  timeStroke = thisStroke - lastStroke;//stide time
  if ((averageStroke * .05) > abs(averageStroke - timeStroke)) { //are we still running great
    R = 0;
    G = 0;
    B = 255;
  }
  else if ((averageStroke * .1) > abs(averageStroke - timeStroke)) { //are we still running great
    R = 255;
    G = 255;
    B = 0;
  }
  else {//are we still running great
    R = 255;
    G = 0;
    B = 0;
  }
  colorWipe(strip.Color(R, G, B), 5); 
}

void sensorRead() {
  if ((millis() - sensorDebounce) > debounceDelay) {
    velostatSensor = analogRead(A1);
    if (velostatSensor > 1000) {
      StrokeTimeArray[StrokeCounter] = millis();
      lastStroke = thisStroke;
      thisStroke = millis();
      StrokeCounter++;
      if (StrokeCounter > numberOfStrokes) {
        StrokeCounter = 0;
      }
    }
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
