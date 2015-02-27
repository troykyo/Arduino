/*
fht_adc.pde
guest openmusiclabs.com 9.5.12
example sketch for testing the fht library.
it takes in data on ADC0 (Analog0) and processes them
with the fht. the data is sent out over the serial
port at 115.2kb.  there is a pure data patch for
visualizing the data.
*/
//shin: mod with mapping of rgb to frequency
//how-to guide: http://shin-ajaran.blogspot.sg/2014/11/arduino-spectrum-analyzer-for-music-to.html
#define LOG_OUT 1 // use the log output function
#define FHT_N 256 // set to 256 point fht

#include <FHT.h> // include the library
//shin: common anode RGB connected to pin3,4,5,6; A0 is eletctret amplifier output
int ledG = 3;//pwm
int ledA = 4;//anode. pull high  
int ledR = 5;//pwm
int ledB = 6;//pwm

//3 chn select at deliberate
int chnLow = 8;
int chnMid = 12;
int chnHigh = 28;
  
//max val
int valMin = 0;
int valMax = 190;  
//bias to reduce on low and increase on high  
int bias = 0;//+- bias to output
int valW=0;
//low pass then avg the 3 grp  
uint16_t tempLow = 0;
uint16_t tempMid = 0;
uint16_t tempHigh = 0;
 
void setup() {
  Serial.begin(115200); // use the serial port
  TIMSK0 = 0; // turn off timer0 for lower jitter
  ADCSRA = 0xe5; // set the adc to free running mode
  ADMUX = 0x40; // use adc0 as A0
  DIDR0 = 0x01; // turn off the digital input for adc0

  pinMode(ledR, OUTPUT);
  pinMode(ledA, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
   //diagnostic led
   diagLed();   
} 

void loop() {
   //bias
   randomSeed(ADMUX);
   bias = random(70,150);

  while(1) { // reduces jitter
	 
    cli();  // UDRE interrupt slows this way down on arduino1.0
    for (int i = 0 ; i < FHT_N ; i++) { // save 256 samples
      while(!(ADCSRA & 0x10)); // wait for adc to be ready
      ADCSRA = 0xf5; // restart adc
      byte m = ADCL; // fetch adc data
      byte j = ADCH;
      int k = (j << 8) | m; // form into an int
      k -= 0x0200; // form into a signed int
      k <<= 6; // form into a 16b signed int
      fht_input[i] = k; // put real data into bins
    }
    fht_window(); // window the data for better frequency response
    fht_reorder(); // reorder the data before doing the fht
    fht_run(); // process the data in the fht
    fht_mag_log(); // take the output of the fht; formula =16*(log^2((img^2 + real^2)^1/2))
    sei();
    Serial.write(255); // send a start byte
    Serial.write(fht_log_out, FHT_N/2); // send out the data; FHT_N/2 contains # of chn
    
	
    //shin: chuck 128chn amplitude to RGB spectrum
    //style1: chuck chn low,mid,high to R,G,B
  
    //triChn(0);//no bias    
    triChn(bias);//with rnd bias
	
	//style2: avg 20chn within low, mid, high band
	//grpChnLowPass();
	
	//style3: threshold chn low=blue, mid green, high red; 
	//treshChn();
  }//end while
}//loop

void diagLed(){
    //on rgb led blue light
	digitalWrite(ledA,HIGH);
	analogWrite(ledR, 0);
    analogWrite(ledG, 255);
    analogWrite(ledB, 255);
	delay(1000);
	digitalWrite(ledA,LOW);
            delay(1000);
        digitalWrite(ledA,HIGH);
	analogWrite(ledR, 255);
    analogWrite(ledG, 0);
    analogWrite(ledB, 255);
    	delay(1000);
	digitalWrite(ledA,LOW);
            delay(1000);
	digitalWrite(ledA,HIGH);
	analogWrite(ledR, 255);
    analogWrite(ledG, 255);
    analogWrite(ledB, 0);
	delay(1000);
}//end diagLed

void triChn(int bias){//read low, mid, high chn
    fht_log_out[chnLow] = map(fht_log_out[chnLow], valMin, valMax, 0, 255); //low
    fht_log_out[chnMid] = map(fht_log_out[chnMid], valMin, valMax, 0, 255); //mid
    fht_log_out[chnHigh] = map(fht_log_out[chnHigh], valMin, valMax, 0, 255); //high
	//with bias
    
    analogWrite(ledB, fht_log_out[chnLow]);
    analogWrite(ledG, fht_log_out[chnMid]-bias);
    analogWrite(ledR, fht_log_out[chnHigh]+bias);
}

void grpChnLowPass(){//grp low pas 60 out of 128 chn into grp of low mid high, avg out in grp
  int numChn = 12;
  for (int i=0; i<numChn; i++) { //i = 256/8 = 32 bins of 8
  //low chn 
  tempLow=fht_log_out[i]+tempLow;
  //mid chn
  tempMid=fht_log_out[(i+11)]+tempMid;
  //high chn
  tempHigh=fht_log_out[i+21]+tempHigh;
  }//end for
	//avg across the grp  
	tempLow = tempLow / numChn;  
	tempMid = tempMid / numChn;
	tempHigh = tempHigh / numChn;
	//map freq to rgb on  pwm pin
    tempLow = map(tempLow, valMin, valMax, 0, 255);
	tempMid = map(tempMid, valMin, valMax, 0, 255);
	tempHigh = map(tempHigh, valMin, valMax, 0, 255);
	//output to rgb
	analogWrite(ledB, tempLow);
    analogWrite(ledG, tempMid);
    analogWrite(ledR, tempHigh);
	
	//output with fade effect1
	//fadePin1(ledB, tempLow);
	//fadePin1(ledG, tempMid);
	//fadePin1(ledR, tempHigh);
	
    //output with fade effect2
	//fadePin2(ledB, ledG, ledR, tempHigh);
	
}//grpChnLowPass

void treshChn(){//on if over threshold low, mid, high
    if(fht_log_out[chnLow]>150){
	analogWrite(ledB, 0);
    analogWrite(ledG, 255);
    analogWrite(ledR, 255);
	delay(50);
	}
	
	else if(fht_log_out[chnHigh]>50){
	analogWrite(ledB, 255);
    analogWrite(ledG, 255);
    analogWrite(ledR, 0);
	delay(50);
	}
	
    else if(fht_log_out[chnMid>110]){
	analogWrite(ledB, 255);
    analogWrite(ledG, 0);
    analogWrite(ledR, 255);
	delay(50);
	}
    

	else{
    randomSeed(ADMUX);
	
    valW = random(0,255);
	analogWrite(ledB, valW);
	valW = random(0,255);
    analogWrite(ledG, valW);
	valW = random(0,255);
    analogWrite(ledR, valW);
	delay(100);
	}

}//end treshChn

void fadePin1(int ledPin, int sFade){

for(int fadeValue = sFade ; fadeValue > 1; fadeValue -=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
}//end fadePin1

void fadePin2(int ledPinR,int ledPinG,int ledPinB, int sFade){

for(int fadeValue = sFade ; fadeValue > 1; fadeValue -=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(ledPinR, fadeValue);
	analogWrite(ledPinG, fadeValue); 
	analogWrite(ledPinB, fadeValue); 	
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);                            
  } 
}//end fadePin
