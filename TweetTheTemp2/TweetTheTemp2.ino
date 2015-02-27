/*
  Tweet the Temp
 
 Meaure the Temp and Humidity with an AM2302 sensor and tweet via a Twitter account using the Temboo Arduino Yun SDK.
 
 This example code is in the public domain. www.troykyo.com
 */

#include <Process.h>
#include <Bridge.h>
#include <Temboo.h>
#include <YunServer.h>
#include <YunClient.h> 
#include "TembooAccount.h" // contains Temboo account information
#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);

YunServer server;
String startString;
long hits = 0;

Process date;
int hours,minutes,seconds;
String timeString;
long delayTime =0;
long minuteDelay =0;
long time = 0;
long numRuns = 0;
int lastrun = 0;
float h = 0;
float t = 0;

// Note that for additional security and reusability, you could
// use #define statements to specify these values in a .h file.
/*
const String TWITTER_ACCESS_TOKEN = "233304728-fMNbzwwVJwQ6C5n5xgLvbwr6PIiGzfR0vi6eCGqU";
 const String TWITTER_ACCESS_TOKEN_SECRET = "Rxe8u50lLQCo9qcMnN9akJUnqKrPq743hqzFMCfKtkpI6";
 const String TWITTER_CONSUMER_KEY = "BgAjT1pVyQ2UOtAVBzIdow";
 const String TWITTER_CONSUMER_SECRET = "eLvkC3tm3X7aT7jJHuulODW2K32SscuHg2CwygrUCa0";
 */

void setup() {
  dht.begin();
  Serial.begin(9600);
  Bridge.begin();
  Console.begin();
  delay(4000);
  if (!date.running())  {
    date.begin("date");
    date.addParameter("+%T");
    date.run();
  }
  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();

  // get the time that this sketch started:
  Process startTime;
  startTime.runShellCommand("date");
  while(startTime.available()) {
    char c = startTime.read();
    startString += c;
  }
}

void loop()
{
  timestamp();
  tempcheck();
  website();
  if (minutes == 38){//tweet onece on the 38
    telltemboo();
    delayTime = millis();
    delay (60000);
  }
  delay(1000*10);
}

void telltemboo(){


  Serial.println("Running SendATweet - Run #" + String(numRuns++) + "...");
  Console.println("Running SendATweet - Run #" + String(numRuns++) + "...");

  // define the text of the tweet we want to send
  //String tweetText(String(t) +"*C  Humidity: " + String(h) + "% ");
  String tweetText(timeString + String(t) + " Celcius " + String(h) + "% Humidity" );

  Serial.println(tweetText);
  Console.println(tweetText);


  TembooChoreo StatusesUpdateChoreo;

  // invoke the Temboo client
  // NOTE that the client must be reinvoked, and repopulated with
  // appropriate arguments, each time its run() method is called.
  StatusesUpdateChoreo.begin();

  // set Temboo account credentials
  StatusesUpdateChoreo.setAccountName(TEMBOO_ACCOUNT);
  StatusesUpdateChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  StatusesUpdateChoreo.setAppKey(TEMBOO_APP_KEY);

  // identify the Temboo Library choreo to run (Twitter > Tweets > StatusesUpdate)
  StatusesUpdateChoreo.setChoreo("/Library/Twitter/Tweets/StatusesUpdate");

  // set the required choreo inputs
  // see https://www.temboo.com/library/Library/Twitter/Tweets/StatusesUpdate/ 
  // for complete details about the inputs for this Choreo

    // add the Twitter account information
  StatusesUpdateChoreo.addInput("AccessToken", TWITTER_ACCESS_TOKEN);
  StatusesUpdateChoreo.addInput("AccessTokenSecret", TWITTER_ACCESS_TOKEN_SECRET);
  StatusesUpdateChoreo.addInput("ConsumerKey", TWITTER_CONSUMER_KEY);    
  StatusesUpdateChoreo.addInput("ConsumerSecret", TWITTER_CONSUMER_SECRET);

  // and the tweet we want to send
  StatusesUpdateChoreo.addInput("StatusUpdate", tweetText);

  // tell the Process to run and wait for the results. The 
  // return code (returnCode) will tell us whether the Temboo client 
  // was able to send our request to the Temboo servers
  unsigned int returnCode = StatusesUpdateChoreo.run();

  // a return code of zero (0) means everything worked
  if (returnCode == 0) {
    Serial.println("Success! Tweet sent!");
    Console.println("Success! Tweet sent!");
  } 
  else {
    // a non-zero return code means there was an error
    // read and print the error message
    while (StatusesUpdateChoreo.available()) {
      char c = StatusesUpdateChoreo.read();
      Serial.print(c);
      Console.print(c);
    }
  } 
  StatusesUpdateChoreo.close(); 
}

void timestamp() {

  // restart the date process:
  if (!date.running())  {
    date.begin("date");
    date.addParameter("+%T");
    date.run();
  }


  //if there's a result from the date process, parse it:
  while (date.available()>0) {
    // get the result of the date process (should be hh:mm:ss):
    timeString = date.readString();    

    // find the colons:
    int firstColon = timeString.indexOf(":");
    int secondColon= timeString.lastIndexOf(":");

    // get the substrings for hour, minute second:
    String hourString = timeString.substring(0, firstColon); 
    String minString = timeString.substring(firstColon+1, secondColon);
    String secString = timeString.substring(secondColon+1);

    // convert to ints,saving the previous second:
    hours = hourString.toInt();
    minutes = minString.toInt();
    seconds = secString.toInt();

    // print the time:
    if (hours <= 9) Console.print("0");    // adjust for 0-9
    Console.print(hours);    
    Console.print(":");
    if (minutes <= 9) Console.print("0");  // adjust for 0-9
    Console.print(minutes);
    Console.print(":");
    if (seconds <= 9) Console.print("0");  // adjust for 0-9
    Console.print(seconds);
  } 
}
void tempcheck(){
  // only try to send the tweet if we haven't already sent it successfully
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  h = dht.readHumidity();
  t = dht.readTemperature();
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
    Console.println("Failed to read from DHT");

  } 
  else {
    Serial.print("\t Humidity: "); 
    Serial.print(h);
    Serial.print(" % ");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.print(" *C");
    Console.print("Humidity: "); 
    Console.print(h);
    Console.print(" %\t");
    Console.print("Temperature: "); 
    Console.print(t);
    Console.print(" *C ");
  }
  time = millis();
  Serial.print(" \tMinutes untill next tweet: ");
  Console.print(" \tMinutes untill next tweet: "); 
  Serial.print(60-(time-delayTime)/60000);
  Console.print(60-(time-delayTime)/60000);
  Serial.print(" \tUptime: ");
  Console.print(" \tUptime: "); 
  Serial.println(time/60000);
  Console.println(time/60000); 
}

void website() {
  // Get clients coming from server
  YunClient client = server.accept();

  // There is a new client?
  if (client) {
    // read the command
    String command = client.readString();
    command.trim();        //kill whitespace
    Serial.println(command);
    Console.println(command);
    // is "temperature" command?
    //if (command == "temperature") {

      // get the time from the server:
      Process time;
      time.runShellCommand("date");
      String timeString = "";
      while(time.available()) {
        char c = time.read();
        timeString += c;
      }
      Serial.println(timeString);
      // print the temperature:
      client.print("Current time on the Yun: ");
      client.println(timeString);
      client.print("<br>Current temperature: ");
      client.print(t);
      client.print(" degrees C");
      client.print(h);
      client.print(" % Humidity");
      client.print("<br>This sketch has been running since ");
      client.print(startString);
      client.print("<br>Hits so far: ");
      client.print(hits);
    //}

    // Close connection and free resources.
    client.stop();
    hits++;
  }
}
















