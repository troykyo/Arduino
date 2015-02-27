/*  Flicker an LED like a candle on ports 3,5,6,9,10,11 using PWM
 by Troy Nachtigall 
 www.troykyo.com 
 */

//constants
const int led[] = {
  -1,3,5,6,9,10,11};// PWM Pins that the LEDs are attached too.

int flickerIntensity; // how bright each individual Flicker is
int maxFlickerIntensity = 150 ; // Maximum brightness for each individual Flicker
int minFlickerIntensity =50; // Miniimum brightness for each individual Flicker
unsigned long flickerLongevity[] = {
  -1,0,0,0,0,0,0}; //duration array for each individual Flicker of the LEDs 
int maxFlickerLongevity = 100; // Maximum time in millaseconds for each individual Flicker
int minFlickerLongevity = 50; // Minimum time in millaseconds for each individual Flicker
unsigned long currentTime = 0; // Variable for the program to ask for the current time.
unsigned long startTime = 0;
unsigned long patternTime = 0;

void setup() {
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  for (int i = 1;i<7;i++){
    pinMode(led[i], OUTPUT); //declare all the LEDs as outputs, Not nesssesarey, but effications
  }
  Serial.begin(9600); // Serial for Testing
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    for (int i = 1;i<7;i++){
      analogWrite(led[i], fadeValue);   
    }    
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 

}

void loop() {
  startTime = millis();
  minFlickerIntensity= random(0,200);
  maxFlickerIntensity = minFlickerIntensity+100;
  patternTime = random(1000,5000);
  while (abs(startTime-currentTime)>patternTime){  
    for (int i = 1;i<7;i++){ // loop to set each LED
      currentTime = millis(); //get the current program time
      if ((flickerLongevity[i])<currentTime){ // test to see it the current Flicker has expired
        flickerIntensity = random (minFlickerIntensity,maxFlickerIntensity); // select a new random intensity
        flickerLongevity[i] = ((random (minFlickerLongevity,maxFlickerLongevity)) + millis()); // select a new random longevity and add it to the current time
        analogWrite(led[i], flickerIntensity);   // write the Flicker to the LED
        Serial.print(i); // which LED
        Serial.print (" "); // Space
        Serial.println(currentTime); //at what time
      }
    }
  }
}



