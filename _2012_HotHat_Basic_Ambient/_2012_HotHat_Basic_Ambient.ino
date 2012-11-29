int brightness = 0;
int leftStrap = 0;
int rightStrap = 0;
int fadeSpeed = 5;

void setup(){
  pinMode (leftStrap, OUTPUT);
  pinMode (rightStrap, OUTPUT);
}

void loop() { //AmbientMode
  for (brightness = 0; brightness < 256; brightness=brightness+fadeSpeed) {     
    analogWrite(leftStrap, brightness); 
    analogWrite(rightStrap, (255-brightness));
  }  
  for (brightness = 255; brightness > 0; brightness=brightness-fadeSpeed) {     
    analogWrite(leftStrap, brightness); 
    analogWrite(rightStrap, (255-brightness));
  }
}

