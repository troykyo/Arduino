/*
  Button Nave
 
 Commands a Raspberry pi to play video when one of six sensors are pressed  on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 7. 
 
 Sends a press count and time between presses to serial
 
 The circuit:
 * Raspberry Pi attached 
 * pushbuttons attached to pin 2 thru 7 from +5V
 * 10K resistor attached to pin 2 thru 7 from ground
 
 
 
 created 2013
 by Troy Nachtigall
 http://www.troykyo.com/Arduino
 */
 
 
const int debounceTime = 100;
// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin []= {
  2,3,4,5,6,7
}
;     // the number of the pushbutton pin
const int ledPin =  13;      // Onboard LED used to indicate proper operation

// variables will change:

int xcounter []={
  0,0,0,0,0,0,0;
}
unsigned long time []={
  0,0,0,0,0,0,0;
}
unsigned long prevtime[]={
  0,0,0,0,0,0,0;
}
int buttonState []={
  0,0,0,0,0,0,0;
}        // variable for reading the pushbutton status
int previousButtonState []={
  0,0,0,0,0,0,0;
}        // variable for reading the pushbutton status
void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  for (int x = 0; x<7; x++){
    pinMode(ledPin[x], OUTPUT);      
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin[x], INPUT);
  }  
}

void loop(){
  // read the state of the pushbutton value:
  for (int x = 0; x<7; x++){
    time[x] = millis();

    buttonState[x] = digitalRead(buttonPin[x]);
    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH:
    if (buttonState == HIGH && (time[x]-previousTime[x]>debounceTime)) {     
      // turn LED on and Serial print count:    
      time[x] = millis();
       Serial.print ("Pulsante ");
      Serial.write(x); 
      Serial.print ("@ ");
      Serial.write(time); 
      xcounter[x] ++;
      Serial.print ("Presso ");
      Serial.print (xcounter);
      Serial.print ("  Volte.  L'ultimo interazione di questo pulsante e' successo in secondi: ");
      Serial.println ((time - prevtime)/1000);
      prevtime = time;
      digitalWrite(ledPin, LOW); 
      while (buttonState == HIGH){// Singular Release Debouncing
        buttonState = digitalRead(buttonPin);
        delay (100);
      }
    } 
    else {
      // turn LED off:
      digitalWrite(ledPin, LOW); 
    }
  }
}



