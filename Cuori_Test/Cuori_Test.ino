int cuore[] = { 
  -1,  12,10,13,11, 9,  2, 6, 4, 3, 5,  45,7,44,46,8, 42 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)
//  -1,  46,10,13,11, 9,  2, 6, 4, 3, 5,  45,7,44,12,8, 42 };     // an array of pins to which Cuori are attached (ZERO INDEXED and +1 Indexed)


int thisCuore[16];


void setup() {
  Serial.begin(9600);
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:

  for (int thisPin = 1; thisPin < 16; thisPin++)  {//output
    pinMode(cuore[thisPin], OUTPUT);
    digitalWrite (cuore[thisPin],  HIGH);
delay (1000);//blink the cuori for half a second (boot test)
    digitalWrite (cuore[thisPin], LOW);   

  }

  for (int thisPin = 1; thisPin < 16; thisPin++)  {
    digitalWrite (cuore[thisPin], HIGH);   
  }  


  for (int thisPin = 1; thisPin < 16; thisPin++)  {
    analogWrite (cuore[thisPin],  100);
    delay (500);//blink the cuori for half a second (boot test)
  }  
}


void loop() {
  for (int thisPin = 1; thisPin < 16; thisPin++)  {//output
    analogWrite (cuore[thisPin],  255);
    for (int thisPin2 = 1; thisPin2 < 16; thisPin2++)  {//output
      if (thisPin2 != thisPin){
       analogWrite (cuore[thisPin2],  255);
        delay (500);
    analogWrite (cuore[thisPin2],  50);
      }
    }
    analogWrite (cuore[thisPin],  50);

  }
}






