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
#include <Udp.h>
#include <EthernetDNS.h>
//Const
const int bird[] = {12,11,9,8,7,6,5,4,3,2,14,15,16,17,18,19}; //array for bird pins
//Variable
long currentTime=0; // Millis Counter
long birdontime[] = {-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // will store last time Bird was turned on
long newArrayTime = 0; //The time at whiche the array was initialzed
unsigned long n;
int birdA[] = {-1,B1,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0}; //array for bird pins
int whichbird = 0; // Counter for selecting bird.
int whichbird2 = 0; // Counter for selecting bird.
int birdonoff;
int localremoteindicator = 0;

// MAC address and IP address for the master controller
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192,168,1,1 };
byte supermaster[] = { 192, 168, 0, 100 }; // Super Master Controller's ip
// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
Server server(80);
Client client(supermaster, 80);

void setup()
{
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
}

void loop()
{
  if ((currentTime - newArrayTime) > 5000){
      if (client.connect()) {
       Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /search?q=arduino HTTP/1.0");
      client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("Local Chirp ");
    LocalRandom ();
    Serial.print (birdA[(whichMaster+16)]);
    Serial.print (" ");
    Serial.print (birdA[(whichMaster)]);
    Serial.print (" ");
    delay(chirplength);
    Serial.println("connection failed");
    
  }
  } 
  
  
  // listen for incoming clients
  Client client = server.available();
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
          client.print("Array updated ");
          client.print ((currentTime - newArrayTime)/1000);
          client.println (" seconds ago.");

          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 17; analogChannel++) {
            
            client.print("Uccellina ");
            client.print(analogChannel);

            currentTime= millis();
            if ((currentTime - birdontime[analogChannel])<5000){
              client.print(" has tweeted ");
              client.print(" for ");
              client.print((currentTime - (birdontime[analogChannel]))/1000);
              client.print(" seconds.    ");
              client.print(currentTime);
              client.print(" - ");
              client.print(birdontime[analogChannel]);
              client.print(" = ");
              client.print(currentTime - (birdontime[analogChannel]));
              }
              else{
              client.print(" is off.   ");
              client.print(birdontime[analogChannel]);
              client.print(" - ");
              client.print(currentTime);
              }
           
           
            client.println("<br />");
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
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}

void LocalRandom () {
  birdA[(whichMaster)] = random (0,255);
  birdA[(whichMaster+16)] = random (0,255);
  TurnOnTheBird();
}

void TurnOnTheBird() {
  for (n=0; n<8; n++){
    birdonoff = bitRead((birdA[(whichMaster)]),n);
    if (birdonoff == 0){
       digitalWrite((bird[(n)]),LOW);
       Serial.print ("off ");}
    if (birdonoff == 1){
       digitalWrite((bird[(n)]),HIGH);
       Serial.print ("on  ");}  
    birdonoff = bitRead((birdA[(whichMaster+16)]),n);
    if (birdonoff == 0){
       digitalWrite((bird[((n+16))]),LOW);
       Serial.print ("OFF ");}
    if (birdonoff == 1){
       digitalWrite((bird[((n+16))]),HIGH);
       Serial.print ("ON  ");}   
  }
}
