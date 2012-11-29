/* Interactive Hat with LED straps that 
 2012 November/December
 */

//Thermistor
int thermistorSensor = A3;    // select the input pin for the thermistor
int temperature = 0;  // variable to store the value coming from the sensor
int temperatureCel = 0; //Temp in Celcius
int thermistorMin = 0; //used for calibrating different thermistors
int thermistorMax = 1024;  //used for calibrating different thermistors

//Straps and Buttons
int leftStrap = 10;     // declare the leftStrap PIN:
int rightStrap = 11;    // declare the rightStrap PIN:
int textileButton = 7;  // declare the textile button:
int buttonState = 0;  // State of the Textile Button:
int lastbuttonState = 0; //State the button was in the last time we checked

//Counters and arrays
long brightness;    // How bright the LED is (Analog):
int route = 3;   // Mode Selector, Starts in Temp
int randomD = 0; //used whenever a random variable is needed
int fadeSpeed = 5; //Controls how fast leds fade
int fadeTime = 5000; //how long a standard fade is in Milliseconds
int someoneCount = 0;// counter for interaction with other hats
unsigned long lastBounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long startTime = 0;    // the  time the interaction starte
unsigned long modeTime = 0;    // the  time the interaction started
int on = 0; //state engine for the onboard LED

void setup() {  
  pinMode(leftStrap, OUTPUT);  // declare the leftStrap as OUTPUT:
  pinMode(rightStrap, OUTPUT);  // declare the rightStrap as OUTPUT:
  pinMode(thermistorSensor, INPUT); // declare the thermistor as INPUT:
  pinMode(textileButton, INPUT); // declare the thermistor as INPUT:
  pinMode(13, OUTPUT);  
  Serial.begin(9600); // Initiate Serial Communications at 9600 baud:
}

void loop() {
  tempCheck(); //check the temp
  Serial.print(" ");
  digitalWrite(13, HIGH);   // turn the Lilypad LED on
  tempCheck();
  Serial.print(temperature);
  Serial.print(" Temperature Mode: The temperature is ");
  Serial.print(temperatureCel); 

  if (temperature > 21){
    fadeTime = map(temperature,thermistorMin,thermistorMax,5000,2000);
    Serial.print (" Fade:");
    Serial.print (fadeTime);
    Serial.println(" High");
    startTime = millis(); //What time is it right now 
    currentTime = millis(); //What time is it right now
    while ((abs(currentTime-startTime))<(fadeTime)) {//do this for half of the fade time
      currentTime = millis(); //What time is it right now 
      brightness = map((currentTime-startTime),1,fadeTime,0,255);
      //Serial.print((currentTime-startTime));
      //Serial.print(" ");
      analogWrite(leftStrap, brightness); 
      if ((currentTime%42)==0){ //wait to change the blink
        brightness = random(0,255); //random brightness
        analogWrite(rightStrap, brightness); 
        //    Serial.print(".");
        //    Serial.print(" "); 
      }
    }
  } 

  else if (temperature < 12){

    fadeTime = map(temperature,thermistorMin,thermistorMax,5000,2000);
    Serial.print (" Fade:");
    Serial.print (fadeTime);
    Serial.println(" Low");
    startTime = millis(); //What time is it right now 
    currentTime = millis(); //What time is it right now
    while ((abs(currentTime-startTime))<(fadeTime)) {//do this for half of the fade time
      currentTime = millis(); //What time is it right now 
      brightness = map((currentTime-startTime),1,2500,0,255);
      if ((currentTime%42)==0){ //wait to change the blink
        brightness = random(0,255); //random brightness
        analogWrite(leftStrap, (255-brightness));
        // Serial.print(".");
        Serial.print(" ");   
      }
      analogWrite(rightStrap, (brightness));
    } 
  }
  else { // Temperature is between 12 and 21 C
    Serial.print (temperature);
    modeTime = millis();
    fadeTime = map(temperature,thermistorMin,thermistorMax,5000,2000);
    Serial.print (" Fade:");
    Serial.print (fadeTime);
    Serial.println(" Med");
    startTime = millis(); //What time is it right now 
    currentTime = millis(); //What time is it right now 
    while ((abs(currentTime-startTime))<(fadeTime/2)) {//do this for half of the fade time
      currentTime = millis(); //What time is it right now 
      brightness = map((currentTime-startTime),0,(fadeTime/2),0,255);
      //Serial.print((currentTime-startTime));
      //Serial.print(" ");
      analogWrite(leftStrap, brightness); 
      analogWrite(rightStrap, brightness);       
    }
  }




  void tempCheck(){
    temperature = analogRead(thermistorSensor);  // read the value from the sensor:  
    temperatureCel = (((temperature-502)*15)/97)+20;
  }//temperature, temperatureCel, thermistorSensor

}







