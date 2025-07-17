/*
  PT_SendingSerialMessages

  Sends serial messages on standard serial output.
  Intended for the Arduino Nano and the TX output pin 1 is used
  to modulate a transmitter.
  LED is flashed for every message sent.
  
  This code is for the first range trials of the transmitter.


 */
 
int led = 13;  // Pin 13 has an LED connected on most Arduino boards.
int blink_delay = 500; //500/2; // ms

int serialSpeedBaud = 9600;

// the setup routine runs once when you press reset:
void setup() {                

  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);

  //Initialize serial and wait for port to open:
  Serial.begin(serialSpeedBaud); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
}

// the loop routine runs over and over again forever:
void loop() {
  
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(blink_delay);

  Serial.println("Hello World!");

//  Serial.print("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(blink_delay);
  
//  Serial.print("UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU");
  Serial.println("David o Peter");
  
  
}



