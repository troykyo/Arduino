//Troy Nachtigall and Klaudia at SLEM Wearable Workshop.

#include <Adafruit_NeoPixel.h>
#define SPEAKER   0    // Speaker on GPIO #0
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
int stepDelay = 10;
int wholeNote = 1000;
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
  if (velostatSensor > 1000) { //are we still running great
    R = 0;
    G = 0;
    B = 255;
    colorWipe(strip.Color(R, G, B), 25); 

  }
  
  else {//are we still running great
    R = 0;
    G = 0;
    B = 0;
    colorWipe(strip.Color(R, G, B), 0); // off
    beep(SPEAKER, 78, wholeNote / 4); // output the tone to digital pin 0
    delay(stepDelay);                 // delay a bit between notes  (also adjustable to taste)

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

void awareDelay() {
  space = millis();
  while ((millis() - space)<stepDelay){
  sensorRead();
  }
}


void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{ // http://web.media.mit.edu/~leah/LilyPad/07_sound_code.html
  int x;
  long delayAmount = (long)(1000000 / frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds * 1000) / (delayAmount * 2));
  for (x = 0; x < loopTime; x++)
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(delayAmount);
    sensorRead();
  }
}
