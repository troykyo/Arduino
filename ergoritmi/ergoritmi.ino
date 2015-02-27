/*
  Cosm sensor client
 
 This sketch connects an analog sensor to Cosm (http://www.cosm.com)
 using a Wiznet Ethernet shield. You can use the Arduino Ethernet shield, or
 the Adafruit Ethernet shield, either one will work, as long as it's got
 a Wiznet Ethernet module on board.
 
 This example has been updated to use version 2.0 of the Cosm.com API. 
 To make it work, create a feed with a datastream, and give it the ID
 sensor1. Or change the code below to match your feed.
 
 
 Circuit:
 * Analog sensor attached to analog in 0
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 15 March 2010
 updated 16 Mar 2012
 */
#include <SPI.h>
#include <Ethernet.h> 

#define APIKEY         "QvHO3MeO-MAnyic7EGVrHqA7y2ySAKxuaWJpTGVoaU8rQT0g" // your cosm api key
#define FEEDID         61250 // your feed ID
#define USERAGENT      "Cosm Arduino Example (61250)" // user agent is the project name
#define smooth 20     //2 smooths the last two nums, 3 smooths the last 3...
#define gsr A0
#define termistore A2
#define piezo A4

// assign a MAC address for the ethernet controller.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
// fill in your address here:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(192,168,1,155);
// initialize the library instance:
EthernetClient client;

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(216,52,233,121);      // numeric IP for api.cosm.com
//char server[] = "api.cosm.com";   // name address for cosm API

unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 10*1000; //delay between updates to Cosm.com



// Matrice, Somma, e Media
int gsrArray[smooth];
int suonoArray[smooth];
int tempArray[smooth];
int gsrAverage = 0;   //  variable per la media 
int tempAverage = 0;   //  variable per la media 
int suonoAverage = 0;   //  variable per la media 
int gsrAverageVecchio = 0;   // variable per la vecchia media
int tempAverageVecchio = 0;   // variable per la vecchia media
int suonoAverageVecchio = 0;   // variable per la vecchia media

// Ciclo, Base, Min e Max
int ciclo = 0; // contatore di cicli
int gsrBase = 0;  //Media di inizia
int tempBase = 0;  //Media di inizia
int suonoBase = 0;  //Media di inizia
int gsrMax = 0;  //Max
int tempMax = 0;  //Max
int suonoMax = 0;  //Max
int gsrMin = 0;  //Min
int tempMin = 0;  //Min
int suonoMin = 0;  //Min

int baud = 9600;//imposta baud rate di communicazione seriale
void setup()
{
  Serial.begin(baud);	// opens serial port, sets data rate to 19200 bps

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // DHCP failed, so use a fixed IP address:
    Ethernet.begin(mac, ip);
  }
}

void loop() {

  for (int i = smooth-1; i >= 1; i--){
    gsrArray[i] = gsrArray[i-1]; //Sposta tutti i numeri adentro la matrice un posto 
    tempArray[i] = tempArray[i-1]; //Sposta tutti i numeri adentro la matrice un posto 
    suonoArray[i] = suonoArray[i-1]; //Sposta tutti i numeri adentro la matrice un posto 
  }
  gsrArray[0] = analogRead(gsr);  //Aggiungere un nuovo lettura allo primo posto della matrice
  tempArray[0] = analogRead(termistore);  //Aggiungere un nuovo lettura allo primo posto della matrice
  suonoArray[0] = analogRead(piezo);  //Aggiungere un nuovo lettura allo primo posto della matrice

  for (int i = 0; i < smooth; i++){
    gsrAverage += gsrArray[i]; //Somma la Matrice
    tempAverage += tempArray[i]; //Somma la Matrice
    suonoAverage += suonoArray[i]; //Somma la Matrice
  }
  gsrAverage = gsrAverage / smooth; //media della somma
  tempAverage = tempAverage / smooth; //media della somma
  suonoAverage = suonoAverage / smooth; //media della somma

  Serial.print(gsrAverage);
  Serial.print("/t");//tab
  Serial.print(tempAverage);
  Serial.print("/t");//tab  
  Serial.print(suonoAverage);
  Serial.print("/t");//tab
  Serial.print(gsrBase-gsrAverage);
  Serial.print("/t");//tab
  Serial.print(tempBase-tempAverage);
  Serial.print("/t");//tab  
  Serial.println(suonoBase-suonoAverage);
  gsrAverageVecchio = gsrAverage;
  tempAverageVecchio = tempAverage;
  suonoAverageVecchio = suonoAverage;
  ciclo ++;
  inviaDati();
}

void inviaDati(){
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  String dataString = "ciclo,";
  dataString += String(ciclo);
  dataString += "\ngsr,";
  dataString += String(gsrAverage);
  dataString += "\nTemp,";
  dataString += String(tempAverage);
  dataString += "\nSuono,";
  dataString += String(suonoAverage);

  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }

  // if you're not connected, and ten seconds have passed since
  // your last connection, then connect again and send data:
  if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
    sendData(dataString);
  }
  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();  
} 
// this method makes a HTTP connection to the server:
void sendData(String thisData) {
  // if there's a successful connection:
  if (client.connect("www.pachube.com", 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.print("PUT /v2/feeds/");
    client.print(FEEDID);
    client.println(".csv HTTP/1.1");
    client.println("Host: api.cosm.com");
    client.print("X-ApiKey: ");
    client.println(APIKEY);
    client.print("User-Agent: ");
    client.println(USERAGENT);
    client.print("Content-Length: ");
    client.println(thisData.length(), DEC);

    // last pieces of the HTTP PUT request:
    client.println("Content-Type: text/csv");
    client.println("Connection: close\n");


    // here's the actual content of the PUT request:

    client.println(thisData); 



  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
  // note the time that the connection was made or attempted:
  lastConnectionTime = millis();
}


// This method calculates the number of digits in the
// sensor reading.  Since each digit of the ASCII decimal
// representation is a byte, the number of digits equals
// the number of bytes:

int getLength(int someValue) {
  // there's at least one byte:
  int digits = 1;
  // continually divide the value by ten, 
  // adding one to the digit count for each
  // time you divide, until you're at 0:
  int dividend = someValue /10;
  while (dividend > 0) {
    dividend = dividend /10;
    digits++;
  }
  // return the number of digits:
  return digits;
}








