unsigned long time;
unsigned long previoustime ;               // last time sequence was initiated
unsigned long lasterror;             // time at which the las error occured
int beat1 ;                 // Single time trial
int beat2 ;                 // Single time trial
int beatdiff;              // differnce in beat
int tolerance = 1;          // tolerence leve for beat difference
int i ;
void setup(){
  Serial.begin(9600);
}
void loop(){
  //Serial.print(" Time: ");
  time = millis(); //prints time since program started
  //Serial.print(time);
  //Serial.print("  previoustime: ");
  //Serial.print(previoustime);
  beat1 = ((time - previoustime));
  beatdiff = (beat1-beat2) ;
  //Serial.println(beatdiff);
  if (beatdiff > tolerance) {
    lasterror = millis();
    Serial.println("|");
    Serial.print("In loop number ");
    Serial.print(i);
    Serial.print(" a differnce of ");
    Serial.print(beatdiff);
    Serial.println(" milliseconds occured.");
    Serial.print("|");
  }
  if ((time-lasterror) > 10000){ 
    Serial.println(i);
    lasterror = time;
  }
  beat2 = beat1;
  previoustime = time;
  i++;
  // wait a second so as not to send massive amounts of data
  delay(100);
}

