#include <Adafruit_NeoPixel.h>

#define PIN 1
int R = 0;
int G = 0;
int B = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

int numberOfStrides = 5;//max 30
unsigned long strideTimeArray[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };;
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
  pinMode(BUZZER, OUTPUT); // Set Trinket/Gemma Digital 0 to output
  pinMode(VELOSENS, INPUT); // Set Trinket/Gemma Digital 0 to output
  // to drive the piezo buzzer (important)
}

void loop() {
  averageStride = 0; //reset the average
  sensorRead(); //read the sensor
  for (int j = 0; j < numberOfStrides; j++) {
    averageStride = averageStride + (strideTimeArray[(j + 1)] - strideTimeArray[(j)]); //add all the stride times together
  }
  averageStride = averageStride / numberOfStrides; //calculate the average
  timeStride = thisStride - lastStride;//stide time
  if ((averageStride*.05) > abs(averageStride-timeStride)){//are we still running great 
R=0;
G=0;
B=255;
}
  else if ((averageStride*.1) > abs(averageStride-timeStride)){//are we still running great 
R=255;
G=255;
B=0;
}
  else {//are we still running great 
R=255;
G=0;
B=0;
}
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
  }
}
