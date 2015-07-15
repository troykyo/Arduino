#define DIR_PIN 12
  #define STEP_PIN 13
  #define sbi(sfr,bit)  ( sfr |=   _BV(bit)  )         // a l'antiga manera. cbi() i sbi() son funcions obsoletes
  #define cbi(sfr,bit)  ( sfr &= ~(_BV(bit)) )  
  //  MS1  MS2  Resolution
  //  L    L    00 Full step (2 phase)
  //  H    L    10 Half step
  //  L    H    01 Quarter step
  //  H    H    11 Eighth step
  //
  // per defecte a la easy driver MS1 = MS2 = HIGH
  
  float microStepping = 8;                             // Valor establert a la easyDriver ( MS1, MS2 )
  long stepsPerRev = 200;                              // característica del motor
  float l = 50;                                        // = 46 +- 20% (el pitjor dels casos es 55.2) característica del motor
  float v = 12;                                        // característica del motor
  float iMax = 0.135;                                  // mesurat amb el tester (cal dividir el resultat per 2 (hi ha 2 bobines))
                                                       // amb la EasyDriver podem controlar iMax abm el potenciòmetre
                                                       
  float ocr2a;                                         // valor de OCR2A ( que depèn de la velocitat màxima del Stepper )
  int ocr2aIni;                                        // valor inicial de OCR2A donada l'acceleració
  
  int accelDuring = 10;                                // Accelera i desaccelera durant 10 Steps
                                                       
  int downCounter = accelDuring;                       // el nombre d'Steps que falten fins acabar la desacceleració
  int upCounter = accelDuring;                         // el nombre d'Steps que falten fins acabar l'acceleració
  int accelDelta;                                      // valor en que varia OCR2A durant l'acceleració 
                                                       // ( p.e. si ha de pasar de 255 a 19 en 10 steps decremeta de 23 en 23 i começa a 249 )
                                                       
  long stepsLeft = 0;                                  // nombre d'Steps que manque per acabar
  boolean running = false;                             // motor is running?
  
  
  
  void setup() {
    unsigned int usDelay;                              // temps d'espera entre Steps en us
      
    Serial.begin(115200);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
  
    usDelay = l * 2000 * iMax / v / microStepping;     // temps d'espera entre steps en microsegons  ( T= L*Imax*2/V (T miliSegons/step) )
    ocr2a = ceil((float)usDelay / 8.0);                // l'enter mes proper donat l'interval del Timer2 ( 8 us )
  
    Serial.println(ocr2a);
  
    if(accelDuring > 0){
      accelDelta = (255 - int(ocr2a) ) / accelDuring;  // OCR2A pasarà del enter mes proper a 255 fins a ocr2a
                                                       // el valor que hem calculat per la velocitat màxima
    Serial.println(accelDelta);
      
      if(accelDelta<=0){
        if(ocr2a < 255){                               // la durada de l'acceleració no pot ser tan gran com esperem
          accelDelta =1;
          ocr2aIni = 255;
          accelDuring = 255 - ocr2a;                   // durada màxima de l'acceleració permesa
          
        }else{                                         // ocr2a = 255, no hi pot haver acceleració
          accelDelta = 0;
          accelDuring = 0;
          ocr2aIni = ocr2a;
        }
        
      }else                                            // acceleració segons la definició
        ocr2aIni = ocr2a + accelDelta * accelDuring;   // calcula el OCR2A inicial donada l'acceleració
        
    }else                                              // no hi ha acceleració
      ocr2aIni = ocr2a;
  
    Serial.println(ocr2aIni);
  
    setTimer2(ocr2aIni);
  
    Serial.print("Inter Step Delay: ");
    Serial.print(usDelay);
    Serial.println(" us");
    Serial.print("Max Speed: ");
    Serial.print( 60000000.0 / ((float)stepsPerRev * microStepping * (usDelay)) );
    Serial.println(" RPM");
    Serial.print("Inter Step Delay programat a Timer2: ");
    Serial.println((int( ceil( (float)usDelay / 8.0 ) ))*8);
    Serial.print("Max Speed Real: ");
    Serial.print( 60000000.0 / ((float)stepsPerRev * microStepping * ((int( ceil( (float)usDelay / 8.0 ) ))*8)) );
  }//// 
  
  
  
  long nVoltes = 1;
  long nSteps = nVoltes * stepsPerRev * microStepping;
  

  void loop(){
    if(!running){
 delay(1000);
      driveStepper(nSteps);
      nSteps = -nSteps;
    }
  }////
  
  
  
  
  
  
  void driveStepper(long lnSteps){
    int dir = (lnSteps > 0)? HIGH:LOW;
    digitalWrite(DIR_PIN,dir);
  
    lnSteps = abs(lnSteps);
  
    OCR2A = ocr2aIni;                // reinicialitza el contador (permet acceleració)
    upCounter = accelDuring;
    downCounter = accelDuring;
    running = true;
    stepsLeft = lnSteps;
  }////
  
  
  
  void setTimer2(int lusDelay) {
  
    //http://arduino.cc/en/Tutorial/SecretsOfArduinoPWM
    // The ATmega328P has three timers known as Timer 0, Timer 1, and Timer 2
    // Each timer has two output compare registers 
    // Each of the timers has a prescaler that generates the timer clock by dividing
    //         the system clock by a prescale factor such as 1, 8, 64, 256, or 1024
    //         Note that Timer 2 has a different set of prescale values from the other timers
    // The Arduino has a system clock of 16MHz and the timer clock frequency will be
    //         the system clock frequency divided by the prescale factor
    // The timers can also generate interrupts on overflow and/or match against either output compare register
    //
    // TCCRnA and TCCRnB. The Timer/Counter Control Registers hold the main control bits
    //            for the timer. (Note that TCCRnA and TCCRnB do not correspond to the outputs A and B.) 
    // TCCRnA and TCCRnB hold several groups of bits: 
    //     Waveform Generation Mode bits (WGM): these control the overall mode of the timer.
    //         (These bits are split between TCCRnA and TCCRnB.) 
    //     Clock Select bits (CS): these control the clock prescaler 
    //     Compare Match Output A Mode bits (COMnA): these enable/disable/invert output A 
    //     Compare Match Output B Mode bits (COMnB): these enable/disable/invert output B 
    //
    // OCRnA and OCRnB. The Output Compare Registers set the levels at which outputs A and B will be affected
    //
    // TIMSK2 – Timer2 Interrupt Mask Register
    //     OCIE2B: Timer2 Output Compare Match B Interrupt Enable
    //     OCIE2A: Timer2 Output Compare Match A Interrupt Enable
    //     TOIE2:  Timer2 Overflow Interrupt Enable
    //
    // Timer 1 is a 16-bit timer and has additional modes. Timer 2 has different prescaler values
    //
    // The Arduino uses Timer 0 internally for the millis() and delay() functions
    // OC0A pin  6   OC0B pin  5
    // OC1A pin  9   OC1B pin 10
    // OC2A pin 11   OC2B pin  3 
  
    cli();                           // plana 10. Bit 7 Clear interrupts
  
    cbi(TCCR2A, COM2A0 );            // plana 158. Table 17-2. Normal port operation, OC0A disconnected. 
    cbi(TCCR2A, COM2A1 );            // 00 deconecta el pin A del timer2
  
    cbi(TCCR2A, WGM20  );            // TCCR2A Regitre A de control del timer 2
    sbi(TCCR2A, WGM21  );       // plana 160 i 149. Clear Timer on Compare
    cbi(TCCR2B, WGM22  );            // WGM2 = 010 ==> mode of operation Clear Timer on Compare (CTC)
                                     // The counter value TCNT2 increases until TCNT2 == OCR2A, 
                                     // and then counter (TCNT2) is cleared
                                     // repeteix el cilce 0 --> valor ( valor clocks )
  
    sbi(TCCR2B, CS22   );            // TCCR2B Regitre B de control del timer 2
    cbi(TCCR2B, CS21   );       // Plana 162
    sbi(TCCR2B, CS20   );            // CS2 = 101 prescaler = 128 ==> 128/16.000.000 = 0.000008 s-1 = 8us-1
                                     // màxim temps que es pot contar = 8 * 255 = 2040 us
  
    sbi(TIMSK2, OCIE2A  );           // Timer2 Output Compare Match A Interrupt Enable. plana 163
  
    cbi(ASSR, AS2);              // AS2 = 0 clocked from the I/O clock
                                     // plana 164. Asynchronous Status Register
                                     // When AS2 is written to zero, Timer/Counter2 is clocked from the I/O clock, clkI/O.
                                     // When AS2 is written to one, Timer/Counter2 is clocked from a crystal Oscillator
                                     // connected to the Timer Oscillator 1 (TOSC1) pin.    
  
    OCR2A = lusDelay;                //  si p.e. OCR2A = 21 --> 21*0.000008 = 168us-1  . cridem la funcio un cop cada 168 us. plana 162
  
    TCNT2 = 0;                       // reset Timer2 counter
  
    sei();                           // Enable Interrupts
  }////
  
  
  
  void stopTimer2() {
    cbi(TIMSK2, OCIE2A  );           // Timer2 Output Compare Match A Interrupt Disable. plana 163
  }////
  
  
  
                                     
  ISR(TIMER2_COMPA_vect) {           // Timer2 Output Compare Match A Interrupt
                                     // definició dels vectors a Arduino\hardware\tools\avr\avr\include\iom328p.h     
                                     // definitions for ATmega328P
    if(stepsLeft > 0){
      if(stepsLeft == downCounter){  // ha de desaccelerar
        downCounter--;
        OCR2A += accelDelta;         // incrementa el temps entre Steps en CS22:0 us (el proper Step es produirà 8 us mes tard)
      }
      else if(upCounter >0){         // ha d'accelerar
        upCounter--;
        OCR2A -= accelDelta;         // decrementa el temps entre Steps en CS22:0 us (el proper Step es produirà 8 us abans)
      }
      digitalWrite(STEP_PIN, HIGH);  // envia el pols a la EasyDriver per avançar 1 Step
      digitalWrite(STEP_PIN, LOW);   // A low-to-high transition on the STEP input sequences the translator 
                                     // and advances the motor one increment.       
                                     // Minimum STEP Pulse Width 1.0 μs (plana 7 de 'A3967.pdf')
                                     // la intruccio NOP triga 1 Clock ( 0,0625 us = 62.5 ns ) per tant
                                     // la instrucció digitalWrite ha de trigar més de 16 Clocks
                                     // mirar el codi a 'wiring_digital.c'
                                     // segons els forums 'digitalWrite()' sembla trigar entre 6 i 9 us
                                     // depenent de si el port es PWM o no
                                     // http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1230286016
      stepsLeft--;
    }
    else                             // para el motor
      running = false;
  }////
