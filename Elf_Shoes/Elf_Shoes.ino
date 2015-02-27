/* Interactive Hat with LED straps that 
 2012 November
 1. Party Mode
 2. Ambient Mode
 3. Temp Mode
 4. Someone is Hot Mode
 5. Someone is Cold Mode
 */

//Sensors
int frontSensor = A3;    // select the input pin for the thermistor
int backSensor = A0;  // variable to store the value coming from the sensor
int strechSensor = 0; //Temp in Celcius
int stretchMin = 0; //used for calibrating different thermistors
int stretchMax = 1024;  //used for calibrating different thermistors
int frontSensorState = 0;  // State of the Textile Button:
int previousFrontSensorState = 0; //State the button was in the last time we checked
int frontSensorState = 0;  // State of the Textile Button:
int previousFrontSensorState = 0; //State the button was in the last time we checked


//LEDs
int ledPins[] = { 
  2, 7, 4, 6, 5, 3 };       // an array of pin numbers to which LEDs are attached
int pomPom = 11;    // declare the backSensor PIN:


//Counters and arrays
long brightness;    // How bright the LED is (Analog):
int route = 3;   // Mode Selector
int previousRoute = 0; //remember the previouse mode
int randomD = 0; //used whenever a random variable is needed
int fadeSpeed = 5; //Controls how fast leds fade
int fadeTime = [] {
  50,400,400,400,100,}; //how long a standard fade is in Milliseconds
int someoneCount = 0;// counter for interaction with other hats
unsigned long lastBounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long startTime = 0;    // the  time the interaction starte
unsigned long modeTime = 0;    // the  time the interaction started
unsigned long syncTime = 0;    // the  time the interaction started
unsigned long someoneTime = 0;    // the  time the interaction started
unsigned int stepTime [5] = {
  400,400,400,400,400,};//Array to calculate how long each step is

int sendTimeLength = 6; //number of chrachters in the send Time array.  Remember to start counting with 0.
int on = 0; //state engine for the onboard LED


void setup() {  
  pinMode(frontSensor, INPUT);  // declare the frontSensor as INPUT:
  pinMode(backSensor, INPUT);  // declare the backSensor as INPUT:
  pinMode(stretchSensor, INPUT); // declare the stretchSensor as INPUT:
  pinMode(pomPom, OUTPUT); // declare the pomPom as OUTPUT:
  pinMode(13, OUTPUT);  
  for (int i = 0; i < 5; i++) {
  pinMode(ledPins[i], OUTPUT); // declare the pomPom as OUTPUT:
  digitalWrite (ledPins[i],HIGH);
  } 
  Serial.begin(9600); // Initiate Serial Communications at 9600 baud:
}

void loop() {
  currentTime = millis();//get the current time.
  irCheck(); //check for messages
  buttonCheck(); //check for button touches
  tempCheck(); //check the temp
  Serial.print(" ");
  if (temperature < 12){ //Tell the world I am Cold
    sendTime[5]=550;
  }
  if (temperature > 21){  //Tell the world I am Hot
    sendTime[5]=700;
  }
  if (route == 1) {
    sendTime[5]=100;
    previousRoute = route;
    SendIR();
    PartyMode();
  } 
  else if (route == 2) {
    sendTime[5]=250;
    previousRoute = route;
    SendIR();
    AmbientMode();
  }
  else if (route == 3) {
    sendTime[5]=400;
    previousRoute = route;
    SendIR();
    TempMode();
  }

  else if (route == 4) { // Someone is Cold Mode
    analogWrite(frontSensor, 255); 
    analogWrite(backSensor, 255);
    SendIR();
    digitalWrite(13, on ? HIGH : LOW);
    PartyMode();
  }
  else if (route == 5) { // Someone is Hot Mode
    analogWrite(frontSensor, 255); 
    analogWrite(backSensor, 255);
    delay (1000);    
    SendIR();
    AmbientMode();
    ;
  }
  else
    digitalWrite(13, HIGH);   //Sanity Check, Route is not right, send a 2 sec alarm
  delay (2000);
  digitalWrite(13, LOW);   //
  delay (1000);
}

void PartyMode() {

  Serial.println("Party Mode");     //Party Mode
  while ((abs(currentTime-startTime))<5000) {
    if (route != 1) {
      break;
    }//Make sure the button was not pressed
    beats();
    buttonCheck();
    if (route != 1){
      break;
    }
  }


  if (route == 1) {//Make sure the button was not pressed

    digitalWrite(frontSensor, LOW);    // turn the Left Strap off
    digitalWrite(13, LOW);    // turn the Left Strap off
    digitalWrite(backSensor, HIGH);   // turn the Right Strap on
    startTime = millis(); //What time is it right now 
    while ((abs(currentTime-startTime))<(random(50,200))) {//do this for .5-1 seconds
      buttonCheck();
      if (route != 1){
        break;
      }
    }
    SendIR();
  }    
}      



void AmbientMode() {
  //Ambient Mode
  fadeTime=5000;
  startTime = millis(); //What time is it right now 
  currentTime = millis(); //What time is it right now 
  Serial.print("Ambient Mode ");
  Serial.println(" Fade 1");
  while ((abs(currentTime-startTime))<(fadeTime/2)) {//do this for half of the fade time
    digitalWrite (13, HIGH);
    currentTime = millis(); //What time is it right now 
    brightness = map((currentTime-startTime),1,2500,0,255);
    //Serial.print(brightness);
    analogWrite(frontSensor, brightness); 
    analogWrite(backSensor, (255-brightness));       
    buttonCheck();
    SendIR();
  } 
  if (route == 2) {//Make sure the button was not pressed 
    currentTime = millis(); //What time is it right now (Sanity Check)
    Serial.println(" Fade 2");
    while ((abs(currentTime-startTime))<(fadeTime)) {//do this for half of the fade time
      digitalWrite (13,LOW);
      currentTime = millis(); //What time is it right now 
      brightness = map((currentTime-startTime),2500,5000,0,255);
      analogWrite(frontSensor, (255-brightness)); 
      analogWrite(backSensor, brightness);       
      //      Serial.print(brightness);
      buttonCheck();
      SendIR();
      if (route != 2){
        break;
      }
      Serial.println(" Fade Complete");  
    }

  }
}



void TempMode() {
  digitalWrite(13, HIGH);   // turn the Lilypad LED on
  tempCheck();

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
      analogWrite(frontSensor, brightness); 
      if ((currentTime%42)==0){ //wait to change the blink
        brightness = random(0,255); //random brightness
        analogWrite(backSensor, brightness); 
        //    Serial.print(".");
        //    Serial.print(" "); 
      }
      buttonCheck();
      if (route != 3){
        break;
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
        analogWrite(frontSensor, (255-brightness));
        // Serial.print(".");
        Serial.print(" ");   
      }
      analogWrite(backSensor, (brightness));
      buttonCheck();
      SendIR();
      if (route != 3){
        break;
      }
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
      analogWrite(frontSensor, brightness); 
      analogWrite(backSensor, brightness);       
      buttonCheck();
      if (route != 3){
        break;
      }
    }
    SendIR();
  }

  currentTime = millis(); //What time is it right now (Sanity Check)
  Serial.println(" Temp Down Fade");
  while ((abs(currentTime-startTime))<(fadeTime)) {//do this for half of the fade time
    currentTime = millis(); //What time is it right now 
    brightness = map((currentTime-startTime),(fadeTime/2),fadeTime,0,255);
    analogWrite(frontSensor, brightness); 
    analogWrite(backSensor, brightness);       
    frontSensorState = digitalRead(textileButton);   // read the value from the textile sensor:
    currentTime = millis(); //What time is it right now //What time is it right now
    buttonCheck();
    if (route != 3){
      break;
    }
  }
  SendIR();  
}

void someOneIsHotMode(){
  AmbientMode();
}

void someOneIsColdMode(){
  PartyMode();
}

void irCheck() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    decodeTime = millis();
    dump(&results);
    SendIR();
    irrecv.enableIRIn(); 
    irrecv.resume(); // Receive the next value
  }
}

void buttonCheck() {	//Checks the textile button.
  frontSensorState = digitalRead(textileButton);	// read the value from the textile sensor:
  currentTime = millis();	//What time is it right now 
  if (frontSensorState == LOW) { 	//check to make sure the button was released
    previousFrontSensorState=0;	//Counter to indicate if the button was pressed or not the previous time the button was checked
  }  
  if (frontSensorState == HIGH){		//button is pressed
    delay(debounceDelay);  	//False Positive Debounce Delay
    frontSensorState = digitalRead(textileButton);   	// read the value from the textile sensor:  
    if ((frontSensorState == HIGH) && (previousFrontSensorState=0) && ((abs(currentTime-lastBounceTime))>1000)){	//Is the button pressed?  Has the button been released? Has it been at least 1 second since the last press? 
      lastBounceTime = millis();	//reset the debounce time
      previousFrontSensorState=1; 	// set the counter to Pressed
      digitalWrite(13, LOW);   // turn the Lilypad LED off (debug)
      modeTime = millis();   
      route = route + 1; // Go to next Mode
      if (route == 4){//reset if route is 4
        route=1;
      }
    }
  }
}

void tempCheck(){
  temperature = analogRead(thermistorSensor);  // read the value from the sensor:  
  temperatureCel = (((temperature-502)*15)/97)+20;
  Serial.print(temperature);
  Serial.print(" Temperature Mode: The temperature is ");
  Serial.print(temperatureCel); 
}

void dump(decode_results *results) {// Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  // void * to work around compiler issue
  //void dump(void *v) 
  //  decode_results *results = (decode_results *)v
  currentTime=millis();
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.println("Could not decode message");
  } 
  else {
    if (results->decode_type == NEC) {
      Serial.print("Decoded NEC: ");
    } 
    else if (results->decode_type == SONY) {
      Serial.print("Decoded SONY: ");
    } 
    else if (results->decode_type == RC5) {
      Serial.print("Decoded RC5: ");
    } 
    else if (results->decode_type == RC6) {
      Serial.print("Decoded RC6: ");
    }
    Serial.print(results->value, HEX);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(" bits)");
  }
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  for (int i = 0; i < count; i++) {

    if ((i % 2) == 1) {
      RecievedTime[i]=results->rawbuf[i]*USECPERTICK;
      Serial.print(RecievedTime[i], DEC);
    } 
    else {
      //     Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
      RecievedTime[i]=results->rawbuf[i]*USECPERTICK;
      Serial.print("-");
      Serial.print(RecievedTime[i], DEC);
    }
    Serial.print(" ");
  }
  ResetTime();
  Serial.println("");
}

void SendIR(){
  currentTime = millis(); //What time is it right now 
  if (abs(syncTime-currentTime)>500){ //if the next sync time is more than 1/2 of a second away send the IR.
    noInterrupts();
    Serial.print("IR>");

    irsend.sendRaw(sendTime,sendTimeLength,38); // Send IR Timer
    interrupts() ;
    irrecv.resume(); // Receive the next value//missing code to start recieving again.    
  }
}

void ResetTime(){
  currentTime = millis(); //What time is it right now 
  decodeTime = (millis()-decodeTime);
  if (((abs((abs(RecievedTime[2]))-controlbitIR))<checkTimeIR)&&((abs((abs(RecievedTime[3]))-controlbitIR))<checkTimeIR)&&((abs((abs(RecievedTime[4]))-controlbitIR))<checkTimeIR)){//three check bits to ensure good data, accurate ot 50ms
    if ((RecievedTime[6]>499) && (RecievedTime[6]>601)){//Someone is cold signal is recieved from another hat
      previousRoute = route;
      route == 4;
      someoneTime = millis();
      someoneCount = 0;
    }
    else if ((RecievedTime[6]>649) && (RecievedTime[6]>751)){//Someone is hot signal is recieved from another hat
      previousRoute = route;
      route == 5;
      someoneTime = millis();
      someoneCount = 0;
    }
    else if (RecievedTime[6]<500){//Recieved a signal that someone is comfortable
      someoneCount ++;
    }
  }
  if (((abs(someoneTime - currentTime))> 30*1000) || (someoneCount>10)){ //if 30 seconds has passed or 10 normal readings have been received go back to normal
    route = previousRoute;
  }
}
void beats(){//for party mode
  randomD = random(1,4);
  Serial.print(" ");
  Serial.println(randomD);
  analogWrite(11, 0); 
  analogWrite(9, 0); 
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
          analogWrite(11, brightness); 
          analogWrite(9, (255-abs(brightness*2-255))); 
        }
        if ((randomD == 2)){
          analogWrite(9, (255-abs(brightness*2-255))); 
          analogWrite(11, (255-abs(brightness*2-255))); 
        }  
        if ((randomD == 3)){
          analogWrite(9, brightness); 
          analogWrite(11, brightness);   
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
          analogWrite(11, brightness); 
          analogWrite(9, (255-abs(brightness*2-255))); 
        }
        if ((randomD == 2)){
          analogWrite(9, brightness);
          analogWrite(11, (255-abs(brightness*2-255))); 
        }  
        if ((randomD == 3)){
          analogWrite(9, brightness); 
          analogWrite(11, brightness);   
        } 
      }
    }
  }
}



