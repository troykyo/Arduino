#include <SPI.h>
#include <Ethernet.h>
#include <Udp.h>
#include <EthernetDNS.h>
#include <Twitter.h>

// Ethernet Shield Settings
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// substitute an address on your own network here
byte ip[] = { 192, 168, 0, 98 };

// Your Token to Tweet (get it from http://arduino-tweet.appspot.com/)
Twitter twitter("233304728-50Is9NlDildFx4gHktZeBAWlvgChtgzD2SKIZYWo");

// Message to post
char msg[] = "This ";
char lastmsg[] = "default";

void setup()
{
  Ethernet.begin(mac, ip);
  Serial.begin(9600); 
}

void loop()
{  
  msg  = Serial.read ();
  if (msg != lastmsg) {  
    Serial.println("connecting ...");
    if (twitter.post(msg)) {
      // Specify &Serial to output received response to Serial.
      // If no output is required, you can just omit the argument, e.g.
      // int status = twitter.wait();
      int status = twitter.wait(&Serial);
      if (status == 200) {
        Serial.println("OK.");
      } else {
        Serial.print("failed : code ");
        Serial.println(status);
      }
    } else {
      Serial.println("connection failed.");
  }
}
