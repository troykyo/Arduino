/*
Elena Air a Fiore
 connect to A1 to start testing. it will needs about 20s to start 
 by Troy Nachtigall
 */
#include"AirQuality.h"
#include"Arduino.h"
#include <Servo.h> 

AirQuality airqualitysensor;
int current_quality =-1;
int current_reading = 0;
int qualita_min = 100;
int qualita_max = 600;
int ultimo_quality = 0;
int counter = 1;
long timer = 0;
long time = -20000;
int mode = 50;

Servo servo1;  // create servo object to control a servo 
Servo servo2;  // create servo object to control a servo 
Servo servo3;  // create servo object to control a servo 

// a maximum of eight servo objects can be created 

int pos = 0;    // variable to store the servo position 
int pos_finale = 0;

void setup()
{
  Serial.begin(9600);
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object 
  servo2.attach(7);  // attaches the servo on pin 9 to the servo object 
  servo3.attach(5);  // attaches the servo on pin 9 to the servo object 
  servo1.write(pos);              // tell servo to go to position in variable 'pos' 
  servo2.write(pos);              // tell servo to go to position in variable 'pos' 
  servo3.write(pos);              // tell servo to go to position in variable 'pos' 
  digitalWrite(13,LOW);
  airqualitysensor.init(14);
 digitalWrite(13,HIGH);
}
void loop()
{
  time = millis();
  current_quality=airqualitysensor.slope();
  current_reading = airqualitysensor.numero();
  if (current_quality >= 0)// if a valid data returned.
  { 
    if (ultimo_quality =! current_quality){
      Serial.print("\t Quality Change");
      timer = millis();
      mode = 10;
      ultimo_quality = current_quality;  
      pos_finale = map(current_reading,qualita_min,qualita_max,0,180);
      Serial.println(pos_finale);

      if (current_quality==0)
        Serial.println(" High pollution! Force signal active");
      else if (current_quality==1)
        Serial.println(" High pollution!");
      else if (current_quality==2)
        Serial.println(" Low pollution!");
      else if (current_quality ==3)
        Serial.println(" Fresh air");
    }
  }
     
    else if (abs(time-timer)>(30*1000)){
      mode = 50;
      pos_finale = pos_finale + counter;
      if ((pos_finale > 180) || (pos_finale < 1)){
        counter = -counter;
      }
    }
    if (pos > pos_finale){ 
        pos--;
         Serial.print("-");
      }
      if (pos < pos_finale){ 
        pos++;
         Serial.print("+");
      }
      
      Serial.print(pos);
      delay (mode);
      servo1.write(pos);              // tell servo to go to position in variable 'pos' 
      delay (mode);
      servo2.write(180-pos);              // tell servo to go to position in variable 'pos' 
      delay (mode);
      servo3.write(pos*2);              // tell servo to go to position in variable 'pos' 
   
  }


ISR(TIMER2_OVF_vect)
{
  if(airqualitysensor.counter==122)//set 2 seconds as a detected duty
  {

    airqualitysensor.last_vol=airqualitysensor.first_vol;
    airqualitysensor.first_vol=analogRead(A0);
    airqualitysensor.counter=0;
    airqualitysensor.timer_index=1;
    PORTB=PORTB^0x20;
  }
  else
  {
    airqualitysensor.counter++;
  }
}








