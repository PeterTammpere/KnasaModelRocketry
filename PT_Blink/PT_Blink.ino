/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int ASK_modulator = 2; // Port D2
int blink_delay = 500/2; // ms
int pulseCounter = 0;

// the setup routine runs once when you press reset:
void setup() {                

  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);


//Initialize serial and wait for port to open:
  Serial.begin(115200); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // prints title with ending line break 
  Serial.println("Arduino nano...");
}

// the loop routine runs over and over again forever:
void loop() {
  
  Serial.print("Pulse count: ");
  Serial.println(pulseCounter);
  
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(ASK_modulator, HIGH);
  delay(blink_delay);

  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(ASK_modulator, LOW);
  delay(blink_delay);
  
  pulseCounter++;
}


