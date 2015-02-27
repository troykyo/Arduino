/*
  Bird master Controller web server
 
 */

#include <SPI.h>
#include <Ethernet.h>
#include <Udp.h>
#include <EthernetDNS.h>

//Constants
const int bird[] = {
  12,11,9,8,7,6,5,4,3,2,14,15,16,17,18,19}; //array for bird pins
const int arrayLifespan = 9000;
const int chirplength = 1000;
const int whichMaster = 1; 
//Variable
long currentTime=0; // Millis Counter
long birdontime[] = {
  -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // will store last time Bird was turned on
long newArrayTime = 0; //The time at whiche the array was initialzed
unsigned long n;
int birdA[] = {
  -1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //array for bird pins
int whichbird = 0; // Counter for selecting bird.
int whichbird2 = 0; // Counter for selecting bird.
int birdonoff;
int localremoteindicator = 0;
int array1;//Server array value
int array2;//server array value 
int handshake = 0;
char c;
// MAC address and IP address for the master controller
// The IP address will be dependent on your local network:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 
  192,168,0,1 };
byte supermaster[] = { 
  192, 168, 0, 100 }; // Super Master Controller's ip
// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
Server server(80);


void setup()
{
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  Serial.begin (9600);
  delay (1000);
  Serial.println ("Initilized");
}

void loop(){
  
  TurnOnTheBird();
  delay (chirplength);
  Serial.println (" chirp");
  currentTime = millis();
  if ((currentTime - newArrayTime) > arrayLifespan){ 
    newArrayTime = millis();
    Serial.println ("reseting the Array");
    /*if (client.connect()){
      downloadArrayFromServer();
    } 
    else if ((!client.connected())){
      // if you didn't get a connection to the server: */   
      Serial.print("Local Chirp using ");
      LocalRandom ();
      Serial.print (birdA[(whichMaster+16)]);
      Serial.print (" ");
      Serial.print (birdA[(whichMaster)]);
      Serial.println (" ");
    }
  } 
 

  


void LocalRandom () {
  birdA[(whichMaster)] = random (0,255);
  birdA[(whichMaster+16)] = random (0,255);
}

void TurnOnTheBird() {
  for (n=0; n<8; n++){
    Serial.print (n+1);
    Serial.print (" ");
    birdonoff = bitRead((birdA[(whichMaster)]),n);
    if (birdonoff == 0){
      digitalWrite((bird[(n)]),LOW);
      Serial.print ("off ");
    }
    if (birdonoff == 1){
      digitalWrite((bird[(n)]),HIGH);
      birdontime[(whichMaster)] = millis();
      Serial.print ("on  ");
    }  
    birdonoff = bitRead((birdA[(whichMaster+16)]),n);
    if (birdonoff == 0){
      digitalWrite((bird[((n+16))]),LOW);
      Serial.print ("OFF ");
    }
    if (birdonoff == 1){
      digitalWrite((bird[((n+16))]),HIGH);
      birdontime[(whichMaster+16)] = millis();
      Serial.print ("ON  ");
    }   
  }
}  

void downloadArrayFromServer() {
  Serial.println("Connected to Server");
}



