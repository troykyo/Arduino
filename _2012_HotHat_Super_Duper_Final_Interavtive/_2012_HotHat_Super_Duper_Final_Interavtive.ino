/* Interactive Hat with LED straps that 
 2012 November/December
 1. Party Mode
 2. Ambient Mode
 3. Temp Mode
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
int fadeSpeed = 1 ; //Controls how fast leds fade
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
  buttonCheck(); //check for button touches
  tempCheck(); //check the temp
  Serial.print("*");
  if (route == 1) {
    PartyMode();
  } 
  else if (route == 2) {
    AmbientMode();
  }
  else if (route == 3) {
    TempMode();
  }
  else{
    digitalWrite(13, HIGH);   //Sanity Check, Route is not right, send a 2 sec alarm
    delay (2000);
    digitalWrite(13, LOW);   //
    delay (2000);
  }
}

void PartyMode() {

  Serial.println("Party Mode");     //Party Mode
  if (route == 1) {//sainity check
    beats();
  }
  buttonCheck();//Make sure the button was not pressed
}


void AmbientMode() {
  Serial.println("Ambient Mode");
  for (brightness = 0; brightness < 256; brightness=brightness+fadeSpeed) {     
    analogWrite(leftStrap, brightness); 
    analogWrite(rightStrap, (255-brightness));
    buttonCheck();
    delay(10);
    if (route != 2){
      break;
    } 
  } 
  if (route == 2) {//Make sure the button was not pressed 
    for (brightness = 255; brightness > 0; brightness=brightness-fadeSpeed) {     
      analogWrite(leftStrap, brightness); 
      analogWrite(rightStrap, (255-brightness));
      buttonCheck();
      delay(10);
      if (route != 2){
        break;
      }
    }
  }
}


void TempMode() {
  digitalWrite(13, HIGH);   // turn the Lilypad LED on
  tempCheck();
  Serial.print(temperature);
  Serial.print(" Temperature Mode: The temperature is ");
  Serial.print(temperatureCel); 

  if (temperatureCel > 30){
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
      buttonCheck();
      if (route != 3){
        break;
      }
    }
  } 

  else if (temperatureCel < 12){

    fadeTime = map(temperature,thermistorMin,thermistorMax,5000,2000);
    Serial.print (" Fade:");
    Serial.print (fadeTime);
    Serial.println(" Low");
    startTime = millis(); //What time is it right now 
    currentTime = millis(); //What time is it right now
    while ((abs(currentTime-startTime))<(fadeTime)) {//do this for half of the fade time
      currentTime = millis(); //What time is it right now 
      brightness = map((currentTime-startTime),1,2500,0,255);
      if (currentTime==0){ //wait to change the blink
        brightness = random(0,255); //random brightness
        analogWrite(leftStrap, (255-brightness));
        // Serial.print(".");
        Serial.print(" ");   
      }
      analogWrite(rightStrap, (brightness));
      buttonCheck();
      if (route != 3){
        break;
      }
    } 
  }
  else { // Temperature is between 12 and 21 C
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
      buttonCheck();
      if (route != 3){
        break;
      }
    }

    currentTime = millis(); //What time is it right now (Sanity Check)
    while ((abs(currentTime-startTime))<(fadeTime)) {//do this for half of the fade time
      currentTime = millis(); //What time is it right now 
      brightness = map((currentTime-startTime),(fadeTime/2),fadeTime,0,255);
      analogWrite(leftStrap, brightness); 
      analogWrite(rightStrap, brightness);       
      buttonState = digitalRead(textileButton);   // read the value from the textile sensor:
      currentTime = millis(); //What time is it right now //What time is it right now
      buttonCheck();
      if (route != 3){
        break;
      }
    }
  }
}

void buttonCheck() {	//Checks the textile button.
  buttonState = digitalRead(textileButton);	// read the value from the textile sensor:
  currentTime = millis();	//What time is it right now 
  if (buttonState == LOW) { 	//check to make sure the button was released
    lastbuttonState=0;	//Counter to indicate if the button was pressed or not the previous time the button was checked
  }  
  if (buttonState == HIGH){		//button is pressed
    digitalWrite(13, HIGH);   // turn the Lilypad LED off (debug)
    delay(debounceDelay);  	//False Positive Debounce Delay
    buttonState = digitalRead(textileButton);   	// read the value from the textile sensor:  
    if ((buttonState == HIGH) && (lastbuttonState==0) && ((abs(currentTime-lastBounceTime))>1000)){	//Is the button pressed?  Has the button been released? Has it been at least 1 second since the last press? 
      lastBounceTime = millis();	//reset the debounce time
      lastbuttonState=1; 	// set the counter to Pressed
      digitalWrite(13, LOW);   // turn the Lilypad LED off (debug)
      modeTime = millis();   
      route = route + 1; // Go to next Mode
      if (route == 4){//reset if route is 4
        route=1;
      }
      for (int modeBlink = 0; modeBlink < route; modeBlink++) { //blink the onboard LED according to the route ie. route = 2, blink twice
        digitalWrite(13, HIGH);   // turn the Lilypad LED on 
        delay (500);
        digitalWrite(13, LOW);   // turn the Lilypad LED off 
        delay (500);
      }
    }
  }
}// buttonState, currentTime, lastbuttonState, debounceDelay, lastBounceTime, modeTime, route

void tempCheck(){
  temperature = analogRead(thermistorSensor);  // read the value from the sensor:  
  temperatureCel = (((temperature-502)*15)/97)+20;
}//temperature, temperatureCel, thermistorSensor

void beats(){//for party mode
  randomD = random(1,4);
  Serial.print(" ");
  Serial.println(randomD);
  analogWrite(rightStrap, 0); 
  analogWrite(leftStrap, 0); 
  for (int i = 0; i < 10; i++) {
    currentTime = millis(); //What time is it right now (Sanity Check)
    startTime = millis(); //What time is it right now (Sanity Check)
    fadeTime = 400;
    if (i<6){
      Serial.print(i);
      while ((abs(currentTime-startTime))<(fadeTime)) {//do this for half of the fade time
        digitalWrite (13,HIGH);
        currentTime = millis(); //What time is it right now 
        brightness = map((currentTime-startTime),0,fadeTime,0,255); 
        if ((randomD == 1)){
          analogWrite(rightStrap, brightness); 
          analogWrite(leftStrap, (255-abs(brightness*2-255))); 
        }
        if ((randomD == 2)){
          analogWrite(leftStrap, (255-abs(brightness*2-255))); 
          analogWrite(rightStrap, (255-abs(brightness*2-255))); 
        }  
        if ((randomD == 3)){
          analogWrite(leftStrap, brightness); 
          analogWrite(rightStrap, brightness);   
        }
        buttonCheck();
        if (route != 1){
          break;
        }
      }
    }
    if (i>5){ 
      Serial.print(i);
      while ((abs(currentTime-startTime))<(fadeTime/2)) {//do this for half of the fade time
        digitalWrite (13,HIGH);
        currentTime = millis(); //What time is it right now 
        brightness = map((currentTime-startTime),0,fadeTime/2,0,255);
        if ((randomD == 1)){
          analogWrite(rightStrap, brightness); 
          analogWrite(leftStrap, (255-abs(brightness*2-255))); 
        }
        if ((randomD == 2)){
          analogWrite(leftStrap, brightness);
          analogWrite(rightStrap, (255-abs(brightness*2-255))); 
        }  
        if ((randomD == 3)){
          analogWrite(leftStrap, brightness); 
          analogWrite(rightStrap, brightness);   
        } 
        buttonCheck();
        if (route != 1){
          break;
        }
      }
    }
  }
}












