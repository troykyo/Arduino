#include <SPI.h>
#include <Ethernet.h>
#include <Udp.h>
#include <EthernetDNS.h>
#include <Twitter.h>

// Ethernet Shield Settings
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// substitute an address on your own network here
byte ip[] = { 192, 168, 0, 98 };
byte server[] = { 128, 121, 146, 100 };		   // Twitter's ip
Client client(server, 80);

void setup()
{
  Ethernet.begin(mac, ip);
  Serial.begin(9600);

  delay(1000);

  Serial.println("connecting...");

  if (client.connect()) {
    Serial.println("connected");
    client.println("GET /#!/ornithologia");
    client.println();
  } else {
    Serial.println("connection failed");
  }
}

void loop()
{
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;)
      ;
  }
}

