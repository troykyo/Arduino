/* Nolita Bird Watching
 Troy Nachtigall 01 January 2011
 CC Atribution, Share Alike*/

#include <SPI.h>    // SPI for the Ethernet Library
#include <Ethernet.h>  //Ethernet Library for Ethernet Communications

int  whichbird = 0; // Counter for selecting bird.
int whichbird2 = 0; // Counter for selecting bird.
int bird[] = {
  0,1,9,8,7,6,5,4,3,2,14,15,16,17,18,19}; //array for bird pins
long previousMillis = 0;        // will store last time LED was updated



void setup()
{
  //Serial.begin(9600); //initialize //Serial
  delay(3000); // wait
  //Serial.println("Initializing..."); //tell the world we are talking 
  pinMode(0, OUTPUT);     
  pinMode(1, OUTPUT);     
  pinMode(9, OUTPUT);     
  pinMode(8, OUTPUT);     
  pinMode(7, OUTPUT);     
  pinMode(6, OUTPUT);  
  pinMode(5, OUTPUT);     
  pinMode(4, OUTPUT);     
  pinMode(3, OUTPUT);     
  pinMode(2, OUTPUT);       
  pinMode(14, OUTPUT);     
  pinMode(15, OUTPUT);    
  pinMode(16, OUTPUT);   
  pinMode(17, OUTPUT);      
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);           
  //digitalWrite(13, HIGH); //light up the onboard LED
}

void loop ()
{

  for (int whichbird2 = 0; whichbird2 < 17; whichbird2++)  {
    //Serial.print("Accendo uccello "); 
    //Serial.print((whichbird2+1));
    //Serial.print(" su Pin ");
    //Serial.println (bird[(whichbird2)]);
    //Serial.println((whichbird2+1));
    digitalWrite (bird[(whichbird2)], HIGH); // turn on the bird
    digitalWrite(13, HIGH); //light up the onboard LED
    delay (200);
    digitalWrite (bird[(whichbird2)], LOW); // turn on the bird
    digitalWrite(13, LOW); //light up the onboard LED
    delay (1300);
  }  
  delay (13500);
}


