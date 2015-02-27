
/* Nolita Bird Watching
Troy Nachtigall 01 January 2011
CC Atribution, Share Alike*/

#include <SPI.h>    // SPI for the Ethernet Library
#include <Ethernet.h>  //Ethernet Library for Ethernet Communications

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 };
byte ip[] = { 192,168,1,177 };

int  whichbird = 0; // Counter for selecting bird.
int whichbird2 = 0; // Counter for selecting bird.
int bird[] = {12,11,9,8,7,6,5,4,3,2,14,15,16,17,18,19}; //array for bird pins
int birdontime[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};        // will store last time LED was updated
int i;
Server server(80);


void setup()
{
//  serial.begin(9600); //initialize client
  delay(1000); // wait
  //client.println("Initializing..."); //tell the world we are talking
  digitalWrite(13, HIGH); //light up the onboard LED
  Ethernet.begin(mac, ip);
  server.begin();
}

void other ()
{
  Client client = server.available();
  for (int whichbird2 = 0; whichbird2 < 16; whichbird2++)  {
    client.print("Accendo uccello "); 
    client.print((whichbird2+1));
    client.print(" su Pin ");
    client.println (bird[(whichbird2)]);
    client.println(whichbird2);
    digitalWrite (bird[(whichbird2)], HIGH); // turn on the bird
    digitalWrite(13, HIGH); //light up the onboard LED
    for (i=0;i<5000; i++){
   //    webServe();
    }
    digitalWrite (bird[(whichbird2)], LOW); // turn on the bird
    digitalWrite(13, LOW); //light up the onboard LED
    for (int i=0;i<5000; i++){
    //   webServe();
    }
    }  
}

void loop ()
{
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

          // output the value of each analog input pin
          for (int digitalChannel = 0; digitalChannel < 20; digitalChannel++) {
            client.print("Bird ");
            if (bird[(digitalChannel)] == HIGH){ 
              client.print("Bird ");
              client.print(digitalChannel);
              client.print(" is ");
              client.print(digitalChannel);
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
}
