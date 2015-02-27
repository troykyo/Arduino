/*
This is the Master Control Program for the Server that controls the 16 Master Controlers


 */
>>>
// Libraries
#include <SPI.h>
#include <Ethernet.h>
#include <Udp.h>
#include <EthernetDNS.h>
#include <Twitter.h>

// Ethernet Shield Settings
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 100 };
byte server[] = { 128, 121, 146, 100 };		   // Twitter's ip
Client client(server, 80);

//constants
const int whichMaster = 1;
const int chirplength = 5000;

//Variables 
unsigned long n;
int birdA[] = {-1,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0}; //array for bird pins 

void setup() {
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  Serial.println ("Initialized, Let's Tweet... ");
  delay (2000);
}

void resetArray() {
  for (n=1; n<32; n++){
    birdA[(n)] = random (0,255);
    Serial.print (birdA[(n)],BIN);
       Serial.print (" "); 
  }
}

void loop() {
resetArray();
delay(chirplength);
Serial.println (" ");
}
