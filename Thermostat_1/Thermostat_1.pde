/* Thermostat first trial

 */


//Thermistor
int thermistorSensor = A5;    // select the input pin for the thermistor
int temperature = 0;  // variable to store the value coming from the sensor
int temperatureCel = 0; //Temp in Celcius

int thermistorMin = 0; //used for calibrating different thermistors
int thermistorMax = 1024;  //used for calibrating different thermistors

//Straps and Buttons
int leftStrap = 10;     // declare the leftStrap PIN:
int rightStrap = 11;    // declare the rightStrap PIN:
int textilebutton = 7;  // declare the textile button:
int buttonstate = 0;  // State of the Textile Button:

//IR
int checkTimeIR = 50;
int RECV_PIN = 9;//ir pin
IRrecv irrecv(RECV_PIN); //enable IR reception on Irrecv pin
decode_results results; // Decode IR commands 
IRsend irsend;//Enable IR Sending

//Counters and arrays
long brightness;    // random number:
int route = 3;   // Mode Selector Starts in Temp
int fadeSpeed = 5; //Controls how fast leds fade
int fadeTime = 5000; //Time for a fade in Milliseconds
unsigned long lastBounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 500;    // the debounce time; increase if the output flickers
unsigned long currentTime = 0;    // the  time since the program started in Milliseconds
unsigned long startTime = 0;    // the  time the interaction starte
unsigned long modeTime = 0;    // the  time the interaction started
unsigned long syncTime = 0;    // the  time the interaction started
unsigned int RecievedTime [7] = {
  50,400,400,400,100,400,50};//recieved array
unsigned int sendTime[7] = {
  50,50,50,50,1000,502,50};//array to send 
int sendTimeLength = 6; //number of chrachters in the send Time array.  Remember to start counting with 0.

void setup() {  
  pinMode(leftStrap, OUTPUT);  // declare the leftStrap as OUTPUT:
  pinMode(rightStrap, OUTPUT);  // declare the rightStrap as OUTPUT:
  pinMode(thermistorSensor, INPUT); // declare the thermistor as INPUT:
  pinMode(textilebutton, INPUT); // declare the thermistor as INPUT:
  pinMode(13, OUTPUT);  
  Serial.begin(9600); // Initiate Serial Communications at 9600 baud:
}

void loop() {
  currentTime = millis();//get the current time.
     digitalWrite(13, HIGH);   // turn the Lilypad LED on
    temperature = analogRead(thermistorSensor);  // read the value from the sensor:  
    temperatureCel = (((temperature-502)*15)/97)+20;
    Serial.print(temperature);
    Serial.print(" Temperature Mode: The temperature is ");
    Serial.print(temperatureCel);  
}

