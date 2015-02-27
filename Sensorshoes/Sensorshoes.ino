int led1 = 13;
int led2 = 14;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(A4, INPUT);
  digitalWrite(A1, HIGH);
  digitalWrite(A4, HIGH);
 
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  int sensorValue1 = analogRead(A4);

  // print out the value you read:
if (sensorValue < 500){}

  Serial.print(sensorValue);
  Serial.print("\t");
  Serial.println(sensorValue1);

  delay(100);        // delay in between reads for stability
}
n 

