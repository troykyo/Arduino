/*  Flicker an LED like a candle on ports 3,5,6,9,10,11 using PWM
by Troy Nachtigall 

CC Share and Share alike */

//constants
const int led1 = 3;
const int led2 = 5;
const int led3 = 6;
const int spin = 9;

int flickerIntensity; // how bright each individual Flicker is
  int maxFlickerIntensity = 255; // Maximum brightness for each individual Flicker
  int minFlickerIntensity = 127; // Miniimum brightness for each individual Flicker
int flickerLongevity; // how long each each flicker lasts
  int maxFlickerLongevity = 100; // Maximum time in millaseconds for each individual Flicker
  int minFlickerLongevity = 30; // Minimum time in millaseconds for each individual Flicker

void setup() {
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(13, OUTPUT); 
    pinMode(led1, OUTPUT); 
      pinMode(led2, OUTPUT); 
        pinMode(led3, OUTPUT); 
          pinMode(spin, OUTPUT); 
}

void loop() {

  flickerIntensity = random (minFlickerIntensity,maxFlickerIntensity);
  analogWrite(led1, flickerIntensity);   // set the candle LED 
  flickerIntensity = random (minFlickerIntensity,maxFlickerIntensity);
  analogWrite(led2, flickerIntensity);   // set the candle LED 
  flickerIntensity = random (minFlickerIntensity,maxFlickerIntensity);
  analogWrite(led3, flickerIntensity);   // set the candle LED 
  flickerIntensity = random (minFlickerIntensity,maxFlickerIntensity);
  analogWrite(spin, flickerIntensity);   // set the candle LED 
  flickerLongevity = random (minFlickerLongevity,maxFlickerLongevity);
  delay(flickerLongevity);  // wait for the random time
}

