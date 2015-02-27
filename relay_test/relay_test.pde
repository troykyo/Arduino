/* Thermostat Relay test 
Troy Nachtigall */

int relay;
int led;

void setup(){
  
pinMode(relay,OUTPUT);
pinMode(led,OUTPUT); 

digitalWrite(led,HIGH);

for(int i=0,i<10,i++){
  digitalWrite (led,HIGH);
  delay(100);
    digitalWrite (led,LOW);
      delay(100);}
}
void loop(){  
    digitalWrite (led,HIGH);
    digitalWrite (relay,HIGH);
      delay(30000);
      
    digitalWrite (led,LOW);
    digitalWrite (relay,LOW);
      delay(30000);
}

  
