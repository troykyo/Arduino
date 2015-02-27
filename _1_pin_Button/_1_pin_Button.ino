/*
  Single Pin Button and LED
 
 
 Share a single Pin between a LED and pushbutton both attached to pin 2. (Input and Output) 
 
 
 The circuit:
 * LED attached from pin 2 to ground 
 * Pushbutton attached to pin 2 from ground
 
 
 Based upon Button 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 */

// constants won't change. They're used here to 
// set pin number:
const int Pin = 2;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600); //Serial to check what is happening.

  // initialize the pin as an input:
  pinMode(Pin, INPUT); //Set the pin as an input
  digitalWrite(Pin, HIGH); //Activate the internal pull up resistor.  
  digitalWrite(13, HIGH); //Turn on the onboard LED just to be sure the board is working. 
}


void loop(){
  // read the state of the pushbutton value:  
  pinMode(Pin, INPUT); //Set the pin as an input. 
  digitalWrite(Pin, HIGH); //Activate the internal pull up resistor.
  delay (1); //Wait a millisecond for the pinmode to take.  
  buttonState = digitalRead(Pin); //read the state of the button
  digitalWrite(Pin, LOW); //deactivate the internal pull up resistor.
  pinMode(Pin, OUTPUT); //Set the pin as an output. 
  delay (1);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {        
    Serial.println("The light is ON");
    digitalWrite(Pin, HIGH); //Turn on the LED attached to the Pin
    digitalWrite(13, LOW); //Turn off the onboard LED
    delay(5); //This delay increases the LED brighness while decreasing button sensitivity. Best between 1 and 10

  } 
  else {
    // turn LED off:
    Serial.println("The light is OFF");
    digitalWrite(Pin, LOW); 
    digitalWrite(13, HIGH);

  }
}

