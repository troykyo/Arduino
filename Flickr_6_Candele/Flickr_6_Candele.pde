/*  Flicker an LED like a candle on ports 3,5,6,9,10,11 using PWM
by Troy Nachtigall 

CC Share and Share alike */

//constanti
const int led1 = 3;
const int led2 = 5;
const int led3 = 6;
const int led4 = 9;
const int led5 = 10;
const int led6 = 11;

//variabili
int intensita_Luce; // quanto brillante è ogni flicker di luce
  int max_intensita_Luce = 255; // Brilantezza massimo per  ogni flicker di luce 
  int min_intensita_Luce = 127; // // Brilantezza minimo per ogni flicker di luce
int flicker_Longevita; // Quanto tempo in millisecondi dura ogni flicker
  int maxflicker_Longevita = 100; // Massimo tempo in millisecondi dura ogni flicker individuale
  int minflicker_Longevita = 30; // Minimo tempo in millisecondi dura ogni flicker individuale

void setup() { // fa una volta
  // initialize il pin digitlae come output.
  pinMode(3, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT); 
  pinMode(13, OUTPUT); 
  // Pin 13 ha una LED collegata sulla Lillypad.
  digitalWrite (13, HIGH);
}

void loop() { // fa tante volte

  intensita_Luce = random (min_intensita_Luce,max_intensita_Luce); // Intensita luce da random
  analogWrite(led1, intensita_Luce);   // accende lo LED 
  intensita_Luce = random (min_intensita_Luce,max_intensita_Luce); // Intensita luce da random
  analogWrite(led2, intensita_Luce);   // accende lo LED
  intensita_Luce = random (min_intensita_Luce,max_intensita_Luce); // Intensita luce da random
  analogWrite(led3, intensita_Luce);   // accende lo LED  
  intensita_Luce = random (min_intensita_Luce,max_intensita_Luce); // Intensita luce da random
  analogWrite(led4, intensita_Luce);   // accende lo LED  
  intensita_Luce = random (min_intensita_Luce,max_intensita_Luce); // Intensita luce da random
  analogWrite(led5, intensita_Luce);   // accende lo LED
  intensita_Luce = random (min_intensita_Luce,max_intensita_Luce); // Intensita luce da random
  analogWrite(led6, intensita_Luce);   // accende lo LED   
  flicker_Longevita = random (minflicker_Longevita,maxflicker_Longevita);  // Longevita luce da random
  delay(flicker_Longevita);  // asspeta per la Longevita
}

