/*
Beat it Back :: Valentinte's Day Heartbeat Code
 This is the code for creating a Heartbeat using a textile button and blinking it back with an led heart crystal.
 by troykyo
 http://www.troykyo.net
 */
unsigned long beats[42]= {1000,1000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // Array for remembering beat and pause lenghts
const int buttonPin = 16;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status
int whichBeat; // Counter for the beat array
int x; //counter for the beat loop
int timer; //time per beat
int beattimer; //time per beat

void setup() {                   	
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT); // init LED output pin     
  pinMode(buttonPin, INPUT); //init input button pin
}


void loop () {  
Serial.begin(9600); // serial comm, data rate: 9600 bps
//blink the assigned pattern using the array, keep blinking until a new pattern array is entered
  whichBeat = 0; //beat counter reset
  buttonState = digitalRead(buttonPin); //read the button state
    while(buttonState == LOW){ //Blink the array pattern until the 
      if (whichBeat = 41){
        whichBeat = 0; //if the end of the array is reached, return to the begining
      }
      timer = beats[(whichBeat)];
      beattimer = beats[((whichBeat)+1)];
      digitalWrite(ledPin, HIGH);  // turn LED on for the amount of time allocated in the array   
        for (x = 0; x < (abs(beats[(whichBeat)]-(beats[((whichBeat)+1)]))); x ++)
        {  
          buttonState = digitalRead(buttonPin); //read the button state 
          if (buttonState == HIGH){      // bail out on sensor detect
             x = 0;
             break;
          }  
        }
 
            
      whichBeat++; //move to the next number in the array //move to the next number in the array
      digitalWrite(ledPin, LOW); // turn LED off for the amount of time allocated in the array
        for (x = 0; x < abs((whichBeat)-((whichBeat)+1)); x ++)
        {  
          buttonState = digitalRead(buttonPin); //read the button state 
          if (buttonState == HIGH){      // bail out on sensor detect
             x = 0;
             break;
          }  
        }
    whichBeat++; //move to the next number in the array 
    buttonState = digitalRead(buttonPin); //read the button state
    }
    
// Start Recording    
  timer = millis();
  beattimer = millis();
  whichBeat = 0; // reset the array position
    for (x = 0; x < 42; x ++) { //reset the array
      beats[x] = 0;  
    }  
    while ((timer - beattimer) < 3000){ // keep recording as long as there is no break longer than 3 seconds
      buttonState = digitalRead(buttonPin); // check the button
      beattimer = millis();  // set the time of the beat     
      if (buttonState == HIGH){      // read in time on sensor detect        
        buttonState = digitalRead(buttonPin); //read the button state
        whichBeat++; //move to the next number in the array // next beat of the beat cycle
        beats[whichBeat] = (beattimer-timer); // record the pause length into the array
          while(buttonState == HIGH){ // bail out when the button is let go. 
            digitalWrite(ledPin, HIGH); //turn the led on in time with the beat
            buttonState = digitalRead(buttonPin); //read the button state       
          }
        timer = beattimer; // reset the time delay
        whichBeat++; //move to the next number in the array // next beat of the beat cycle
        beattimer = millis();  // set the time of the beat 
        Serial.print (beattimer); // testing line
        Serial.print (", ");        
        beats[whichBeat] = (beattimer-timer); // record the beat length into the array
        } 
  }
}
