int textileButtonFront = A3;  // declare the textile button:
int textileButtonBack = A4;  // declare the textile button:
int buttonStateFront = 0;  // State of the Textile Button:
int buttonStateBack = 0;  // State of the Textile Button:
int previousbuttonStateFront = 0; //State the button was in the previous time we checked
int previousbuttonStateBack = 0; //State the button was in the previous time we checked
unsigned long previousBounceTimeFront = 0;  // the previous time the output pin was toggled
unsigned long previousBounceTimeBack = 0;  // the previous time the output pin was toggled
const unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long frontTime[10];
unsigned long backTime[10];
unsigned long frontCount[10];
unsigned long backCount[10];
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly: 
  buttonStateFront = digitalRead(textileButtonFront);	// read the value from the textile sensor:
  buttonStateBack = digitalRead(textileButtonBack);	// read the value from the textile sensor:

  currentTime = millis();	//What time is it right now 
  if (buttonStateFront == LOW) { 	//check to make sure the button was released
    previousbuttonStateFront=0;	//Counter to indicate if the button was pressed or not the  time the button was checked
    digitalWrite(2, LOW);   // turn the Lilypad LED on
  } 
  if (buttonStateBack == LOW) { 	//check to make sure the button was released
    previousbuttonStateBack=0;	//Counter to indicate if the button was pressed or not the  time the button was checked
    digitalWrite(13, LOW);   // turn the Lilypad LED on
  }   
  if ((buttonStateFront == HIGH) || (buttonStateBack == HIGH)) {		//button is pressed
    digitalWrite(2, HIGH);   // turn the Lilypad LED on
    buttonStateFront = digitalRead(textileButtonFront);   	// double check the value from the textile sensor: 
    buttonStateBack = digitalRead(textileButtonBack);   	// double check the value from the textile sensor: 
    if ((buttonStateFront == HIGH) && (previousbuttonStateFront==0) && ((abs(currentTime-previousBounceTimeFront))>debounceDelay)){	//Is the button pressed?  Has the button been released? Has it been at least 1 second since the previous press? 
      frontTime[(frontCount%10)] = (abs(currentTime-previousBounceTimeFront)
      frontCount++;
      previousBounceTimeFront = millis();	//reset the debounce time
      previousbuttonState=1; 	// set the counter to Pressed
    }
  }
}





