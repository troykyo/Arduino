/*
  Web  Server
 
 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 18 Dec 2009
 by David A. Mellis
 modified 4 Sep 2010
 by Tom Igoe
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192,168,0,100 };

const int arrayLifespan = 5000;
int birdA[] = {-1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //array for bird pins
long mastercontrolerontime[] = {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // will store last time the master contorller updated
long currentTime=0; // Millis Counter
long newArrayTime = 0; //The time at whiche the array was initialzed
int whicharray = 0; // Counter for selecting array.
int whicharray2 = 0; // Counter for selecting array2.
int handshake = 0; //communications handshake
int array1;//Server array value
int array2;//server array value 
unsigned long n;
// Initialize the Ethernet server library
// with the IP address and port you want to use 
Server server(80);

void setup()
{
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin (9600);
  delay (1000);
  Serial.println ("Initilized");
}

void loop()
{
  currentTime = millis();
  if ((currentTime - newArrayTime) > arrayLifespan){ 
    newArrayTime = millis();
    Serial.println ("reseting the Array");
    arrayReset ();
  }
  // listen for incoming clients
  Client client = server.available();
  //Serial.println ("Client Connected");
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();

        for (n=1;n<32;n++){
        server.write (birdA[(n)]);
        Serial.print (birdA[(n)]);
        Serial.print (" ");
        /*handshake = client.read();//Handshake with client
        Serial.print (handshake);
        if (handshake == 42){
          client.println(24);
          array1 = client.read();
          client.println(birdA[(array1)]);
          array2 = client.read();
          client.println(birdA[(array2)]);
          Serial.print ("Array succesfully Master Controler ");
          Serial.print (array1);
          Serial.print (" the value ");
          Serial.println(birdA[(array1)]);
          Serial.print ("Array succesfully Master Controler ");
          Serial.print (array2);
          Serial.print (" the value ");
          Serial.println(birdA[(array2)]);}*/ 
          }
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      handshake = 0;
      // give the web browser time to receive the data
      delay(10);
      // close the connection:
      client.stop();
      }
    }
  }
}  
void arrayReset () {
  for (n=1;n<32;n++){
    birdA[(n)] = random (0,255);
    Serial.print (birdA[(n)]);
    Serial.print (" ");
    }
  Serial.println ("Array Reset");
  
}
