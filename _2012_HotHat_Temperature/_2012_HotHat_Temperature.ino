int thermistorSensor = 0;    // select the input pin for the thermistor
int temperature = 0;  // variable to store the value coming from the sensor
int temperatureCel = 0; // variable to store the calculated temp in Celcius

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(thermistorSensor, INPUT);
  Serial.begin(9600);
}

void loop(){//tempCheck
  temperature = analogRead(thermistorSensor);  // read the value from the sensor:  
  Serial.print("The analog reading is ");
  Serial.print(temperature);
  temperatureCel = (((temperature-502)*15)/97)+20;
  Serial.print("  The temperature is ");
  Serial.println(temperatureCel); 
}


