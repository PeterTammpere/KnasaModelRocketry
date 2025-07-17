//
#include "Wire.h"
#include "I2Cdev.h"
#include "hmc6352.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "t5403.h"
#include "sensors.h"


#define LED_PIN 13 // (Arduino is 13)
const uint16_t sampleTimeMs = 100; // 10 Hz
uint32_t thisSampleTimeMs = 0;	// Time in ms
#define SEPARATOR ","

Sensors sens;
bool blinkState = false;

void setup() {

    // initialize serial communication
    Serial.begin(9600);

    // initialize device
    Serial.println("#Initializing I2C devices...");
    sens.initialize();

    // configure LED for output
    pinMode(LED_PIN, OUTPUT);
    
    // Logging headline
    Serial.print("ms,ms,degrees,m/s2,m/s2,m/s2,deg/s,deg/s,deg/s,m");
    Serial.print("Time,Sample time,Compass heading,AccX,AccY,AccZ,RotX,RotY,RotZ,Altitude");
    Serial.print(SEPARATOR); 

}

void loop()
{
  while ( millis() % sampleTimeMs != 0) 
  {
  }
  thisSampleTimeMs = millis();

  sens.sampleAllSensors();
    // display tab-separated accel x/y/z values
/*    Serial.print("accel:\t");
    Serial.print(axf); Serial.print("\t");
    Serial.print(ayf); Serial.print("\t");
    Serial.println(azf);
*/
  Serial.print(millis());
  Serial.print(SEPARATOR); 
  Serial.print(thisSampleTimeMs);
  Serial.print(SEPARATOR); 

  Serial.print(sens.compassHeading);
  Serial.print(SEPARATOR); 

  Serial.print(sens.acceleration[0]); 
  Serial.print(SEPARATOR); 
  Serial.print(sens.acceleration[1]); 
  Serial.print(SEPARATOR); 
  Serial.print(sens.acceleration[2]); 
  Serial.print(SEPARATOR); 


  Serial.print(sens.rotation[0]); 
  Serial.print(SEPARATOR); 
  Serial.print(sens.rotation[1]); 
  Serial.print(SEPARATOR); 
  Serial.print(sens.rotation[2]); 
//  Serial.print(SEPARATOR); 
  // End of line
  Serial.println();

  //supplyVoltage


  
  // blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}
