/*
Heartbeat :: I <3 Lilypad
 This is the code for creating a Heartbeat using textile buttons and blinking it back with a textile Perfboard heart.
 by troykyo 
 http://www.troykyo.net
*/
 
const int buttonPin1 = 15;     // the number of the pushbutton pin
const int buttonPin2 = 16;     // the number of the pushbutton pin
const int ledPin[] = {-1,2,13,0,1,3,4,5,6,7,8,9,10,11,12,14,14,14,14}; // Array for Led heart pin, change starting from 1
int buttonState = 0;         // variable for reading the pushbutton status
int whichBeat; // Counter for the beat array
int timer = 5000; //time per beat
int beattimer; //time per beat
//int x; //counter for the beat loop

void setup() {                   	
  // initialize the LED pin as an output:
  // pinMode(ledPin, OUTPUT); // init LED output pin     
  pinMode(buttonPin1, INPUT); //init input button pin
  pinMode(buttonPin2, INPUT); //init input button pin
}

void loop () {  
Serial.begin(9600); // serial comm, data rate: 9600 bps
Serial.println("Begin");
//blink the assigned pattern using the array, keep blinking until a new pattern array is entered
  whichBeat = 0; //beat counter reset
  buttonState = digitalRead(buttonPin1); //read the button state
    while(buttonState == LOW){ //Blink the array pattern until the 
      Serial.println("go");
      if (whichBeat < 0){
        whichBeat = 0; //if the end of the array is reached, return to the begining
      }
        for (whichBeat = 0; whichBeat < 16; whichBeat ++){// build up the heart  
          buttonState = digitalRead(buttonPin1); //read the button state 
          Serial.print(whichBeat);
          if (buttonState == HIGH){      // bail out on button sensor detect
             whichBeat = 0; //reset the beat
             break;
            digitalWrite(ledPin[whichBeat], HIGH);  // turn LED on    
            if (whichBeat < 2){ //Skip this the first two times
              digitalWrite(ledPin[(whichBeat-2)], LOW);  // turn the LED three times ago off
            delay (timer);
            }         
          }  
        }
 
        for (whichBeat = 16; whichBeat > 0; whichBeat --)// build up the heart
        {  
          buttonState = digitalRead(buttonPin1); //read the button state 
          if (buttonState == HIGH){      // bail out on button sensor detect
             whichBeat = 0; //reset the beat
             break;
            digitalWrite(ledPin[whichBeat], HIGH);  // turn LED on    
            if (whichBeat > 15){ //Skip this the first two times
              digitalWrite(ledPin[(whichBeat-2)], LOW);  // turn the LED three times ago off
            delay (timer);
            }         
          }  
        }   
      
      
    buttonState = digitalRead(buttonPin1); //read the button state
    }
    
/* Start Recording    
  timer = millis();
  beattimer = millis();
  whichBeat = 0; // reset the array position
    for (x = 0; x < 42; x ++) { //reset the array
      beats[x] = 0;  
    }  
    while ((timer - beattimer) < 3000){ // keep recording as long as there is no break longer than 3 seconds
      buttonState = digitalRead(buttonPin1); // check the button
      beattimer = millis();  // set the time of the beat     
      if (buttonState == HIGH){      // read in time on sensor detect        
        buttonState = digitalRead(buttonPin1); //read the button state
        whichBeat++; //move to the next number in the array // next beat of the beat cycle
        beats[whichBeat] = (beattimer-timer); // record the pause length into the array
          while(buttonState == HIGH){ // bail out when the button is let go. 
            digitalWrite(ledPin, HIGH); //turn the led on in time with the beat
            buttonState = digitalRead(buttonPin1); //read the button state       
          }
        timer = beattimer(); // reset the time delay
        whichBeat++; //move to the next number in the array // next beat of the beat cycle
        beattimer = millis();  // set the time of the beat 
        Serial.print (beattimer); // testing line
        Serial.print (", ");        
        beats[whichBeat] = (beattimer-timer); // record the beat length into the array
        } 
  }*/
}
