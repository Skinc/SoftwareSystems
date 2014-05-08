/*
  

 Author: Allen Downey 
 
 Based on http://arduino.cc/en/Tutorial/AnalogInput
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe

 License: Public Domain
 
 */
 
 
int ledPin = 5;       // select the pin for the LED
int buttonPin1 = 2;
int buttonPin2 = 3;

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin1, INPUT);  
  pinMode(buttonPin2, INPUT);  

  pinMode(ledPin, OUTPUT);
  
  pinMode(13, OUTPUT);  
  pinMode(12, OUTPUT);  
  pinMode(11, OUTPUT);  
  pinMode(10, OUTPUT);  
  pinMode(9, OUTPUT);  
  pinMode(8, OUTPUT);  
  pinMode(7, OUTPUT);  
  pinMode(6, OUTPUT);  
   // TIMER SETUP- the timer interrupt allows preceise timed measurements of the reed switch
  //for mor info about configuration of arduino timers see http://arduino.cc/playground/Code/Timer1
  cli();//stop interrupts

  //set timer1 interrupt
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1 = 0;//initialize counter value to 0;

  OCR1A = 1000; 
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  sei();//allow interrupts
   attachInterrupt(0, buttonInterupt1, RISING);  // Interrupt attached to the button connected to pin 2
  attachInterrupt(3, buttonInterupt2, RISING);  // Interrupt attached to the button connected to pin 3
}

void writeByte(int x) {
  // clear the first to bits and then set them (6,7)
  PORTD = (PORTD & B00111111 ) | (x << 6);
  //set 8-13 as the 3rd bit on. 
  PORTB = x >> 2; 
}

int low = 36;
int high = 255;
int stride = 5;
int counter = low;


ISR(TIMER1_COMPA_vect) {//Interrupt at freq of 1kHz to measure reed switch
  counter += stride;
  if (counter > high) {
    counter = low;
    //Serial.println(counter);
  }

  // write to the digital pins
  writeByte(counter);
}

void buttonInterupt1(){
}

void buttonInterupt2(){
  
}


void loop() {
  int button1 = digitalRead(buttonPin1);
  if (button1) return;
}
