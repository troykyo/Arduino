/* 
by Troy Nachtigall and Lisa 


*/

#define SPEAKER   0    // Speaker on GPIO #0

int stepDelay = 10;
int wholeNote = 1000;
int velostatSensor = 0;
unsigned long lastStride = 0;
unsigned long thisStride = 0;
int space = 0;//used for making an aware delay
void setup() {
  pinMode(SPEAKER, OUTPUT); // Set Trinket/Gemma Digital 0 to output
  // to drive the piezo buzzer (important)
}

void loop() {

  sensorRead();
  beep(SPEAKER, 1568, wholeNote / 4); // output the tone to digital pin 0
  // you can change 400 to different times}
  // delay a bit between notes  (also adjustable to taste)
  beep(SPEAKER, 78, wholeNote / 4); // output the tone to digital pin 0
  delay(stepDelay);                 // delay a bit between notes  (also adjustable to taste)

}

// the sound producing function
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
void awareDelay() {
  space = millis();
  while ((millis() - space)<stepDelay){
  sensorRead();
  }
}

void sensorRead() {
  velostatSensor = analogRead(A1);
  if (velostatSensor > 1000) {
    lastStride = thisStride;
    thisStride = millis();
    wholeNote = thisStride - lastStride;
  }
}
