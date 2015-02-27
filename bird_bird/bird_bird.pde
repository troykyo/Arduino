/* Nolita Bird Watching
Troy Nachtigall 01 January 2011
CC Atribution, Share Alike*/

#include <SPI.h>    // SPI for the Ethernet Library
#include <Ethernet.h>  //Ethernet Library for Ethernet Communications

byte whichbird = 0; // Counter for selecting bird.
byte whichbird2 = 0; // Counter for selecting bird.
byte bird[] = {12,11,9,8,7,6,5,4,3,2,14,15,16,17,18,19}; //array for bird pins
long previousMillis = 0;        // will store last time LED was updated

void Canta(){
  Serial.println("Digita 17 per uscire."); 
  for (byte whichbird2 = 17; whichbird2 > 1; whichbird2--)  {
    digitalWrite(bird[(whichbird2)], LOW);
  }
    while ((whichbird < 17) && (whichbird > 0)){
        Serial.print("Accendo uccello "); 
        Serial.println(whichbird);
        digitalWrite (bird[(whichbird)], HIGH); // turn on the bird
        whichbird = Serial.read();
    }
}

void setup()
{
  Serial.begin(9600); //initialize serial
  delay(1000); // wait
  Serial.println("Initializing..."); //tell the world we are talking
  digitalWrite(13, HIGH); //light up the onboard LED
}

void loop ()
{
whichbird = Serial.read(); 
if ((isDigit(whichbird)) && (whichbird < 17) && (whichbird > 0))  {
  Canta();
}
  whichbird = Serial.read();
  for (byte whichbird2 = 0; whichbird2 < 17; whichbird2++)  {
    whichbird = Serial.read();
    if ((isDigit(whichbird)) && (whichbird < 17) && (whichbird > 0))  {
      Canta();
    }  
    Serial.print(whichbird2);
    Serial.print(" ");
    digitalWrite(bird[(whichbird2)], HIGH);
    for (byte i =0; i<1000; i++){
      if ((isDigit(whichbird)) && (whichbird < 17) && (whichbird > 0))  {
      Canta();
      } 
    }  
  }
  for (byte whichbird2 = 17; whichbird2 > 1; whichbird2--)  {
    whichbird = Serial.read();
    if ((isDigit(whichbird)) && (whichbird < 17) && (whichbird > 0))  {
      Canta();
    }
    digitalWrite(bird[(whichbird2)], LOW);
  }    
}  
  
  
