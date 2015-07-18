#include <Adafruit_NeoPixel.h>

#define PIN 1
int R = 255;
int G = 0;
int B = 255;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(3, PIN, NEO_GRB + NEO_KHZ800);

int numberOfStrides = 5;//max 30
unsigned long strideTimeArray[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
int velostatSensor = 0;
unsigned long averageStride = 0;
unsigned long lastStride = 0;
unsigned long thisStride = 0;
unsigned long timeStride = 0;
unsigned long space = 0;//used for making an aware delay
unsigned long sensorDebounce = 0;//used for making an aware delay
int debounceDelay = 50;
int strideCounter = 0;
int BUZZER = 0;
int VELOSENS = A1;

void setup() {
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket

  strip.begin();
  // End of trinket special code
  
  colorWipe(strip.Color(R, G, B), 500); // Red
  pinMode(BUZZER, OUTPUT); // Set Trinket/Gemma Digital 0 to output
  pinMode(VELOSENS, INPUT); // Set Trinket/Gemma a1 to input
  // to drive the piezo buzzer (important)

  digitalWrite(BUZZER, HIGH);
  delay (1000);
  digitalWrite(BUZZER, LOW);
  delay (1000);
}

void loop() {
  averageStride = 0; //reset the average
  sensorRead(); //read the sensor
  for (int j = 0; j < numberOfStrides; j++) {
    averageStride = averageStride + (strideTimeArray[(j + 1)] - strideTimeArray[(j)]); //add all the stride times together
  }
  averageStride = averageStride / numberOfStrides; //calculate the average
  timeStride = thisStride - lastStride;//stide time
  if ((averageStride * .05) > abs(averageStride - timeStride)) { //are we still running great
    R = 0;
    G = 0;
    B = 255;
    digitalWrite(BUZZER, LOW);
  }
  else if ((averageStride * .1) > abs(averageStride - timeStride)) { //are we still running great
    R = 255;
    G = 255;
    B = 0;
    digitalWrite(BUZZER, LOW);
  }
  else {//are we still running great
    R = 255;
    G = 0;
    B = 0;
    digitalWrite(BUZZER, HIGH);
  }
  colorWipe(strip.Color(R, G, B), 5); // Red

}

void sensorRead() {
  if ((millis() - sensorDebounce) > debounceDelay) {
    velostatSensor = analogRead(A1);
    if (velostatSensor > 1000) {
      strideTimeArray[strideCounter] = millis();
      lastStride = thisStride;
      thisStride = millis();
      strideCounter++;
      if (strideCounter > 9) {
        strideCounter = 0;
      }
    }
    sensorDebounce = millis();
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
