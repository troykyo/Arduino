/*
 Firefly Interactive Lamp 
 */

#include <Ultrasonic.h>
#include <Servo.h> 


#define TRIGGER_PIN1  9
#define TRIGGER_PIN2  11
#define TRIGGER_PIN3  10
#define TRIGGER_PIN4  6
#define TRIGGER_PIN5  1
#define TRIGGER_PIN6  0

#define ECHO_PIN1     13
#define ECHO_PIN2     12
#define ECHO_PIN3     8
#define ECHO_PIN4     7
#define ECHO_PIN5     4
#define ECHO_PIN6     3

Ultrasonic ultrasonic1(TRIGGER_PIN1, ECHO_PIN1);
Ultrasonic ultrasonic2(TRIGGER_PIN2, ECHO_PIN2);
Ultrasonic ultrasonic3(TRIGGER_PIN3, ECHO_PIN3);
Ultrasonic ultrasonic4(TRIGGER_PIN4, ECHO_PIN4);
Ultrasonic ultrasonic5(TRIGGER_PIN5, ECHO_PIN5);
Ultrasonic ultrasonic6(TRIGGER_PIN6, ECHO_PIN6);

Servo servo1;  // create servo object to control a servo 
Servo servo2;  // create servo object to control a servo 
Servo servo3;  // create servo object to control a servo 
Servo servo4;  // create servo object to control a servo 
Servo servo5;  // create servo object to control a servo 
Servo servo6;  // create servo object to control a servo 


long Tempo1 = 0;
long Tempo2 = 0;
long Tempo3 = 0;
long Tempo4 = 0;
long Tempo5 = 0;
long Tempo6 = 0;
long minDist = 1; //Misurata in microsec, non cm
long maxDist = 58; //Misurata in microsec, non cm
float cmMsec;
int val;    // variable to read the value from the analog pin
 
void setup()
  {
  Serial.begin(9600);
    servo1.attach(15);  // attaches the servo on pin 9 to the servo object 
    servo2.attach(16);  // attaches the servo on pin 9 to the servo object 
    servo3.attach(17);  // attaches the servo on pin 9 to the servo object 
    servo4.attach(18);  // attaches the servo on pin 9 to the servo object 
    servo5.attach(19);  // attaches the servo on pin 9 to the servo object 
    servo6.attach(2);  // attaches the servo on pin 9 to the servo object 
  }

void loop()
  {
  
  Tempo1 = ultrasonic1.timing();
  cmMsec = ultrasonic1.convert(Tempo1, Ultrasonic::CM);
  Serial.print("1 MS: ");
  Serial.print(Tempo1);
  Serial.print(", CM: ");
  Serial.print(cmMsec);
  val = map(val, minDist, maxDist, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  val = constrain(val, 0, 179);
  Serial.print(", Servo: ");
  Serial.println(val);
  servo1.write(val);                  // sets the servo position according to the scaled value 
  
  Tempo2 = ultrasonic2.timing();
  cmMsec = ultrasonic2.convert(Tempo2, Ultrasonic::CM);
  Serial.print("1 MS: ");
  Serial.print(Tempo2);
  Serial.print(", CM: ");
  Serial.print(cmMsec);
  val = map(val, minDist, maxDist, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  val = constrain(val, 0, 179);
  Serial.print(", Servo: ");
  Serial.println(val);
  servo2.write(val);                  // sets the servo position according to the scaled value
 
  Tempo3 = ultrasonic3.timing();
  cmMsec = ultrasonic3.convert(Tempo3, Ultrasonic::CM);
  Serial.print("1 MS: ");
  Serial.print(Tempo3);
  Serial.print(", CM: ");
  Serial.print(cmMsec);
  val = map(val, minDist, maxDist, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  val = constrain(val, 0, 179);
  Serial.print(", Servo: ");
  Serial.println(val);
  servo3.write(val);                  // sets the servo position according to the scaled value  
 
  }
