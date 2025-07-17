//
#include "Wire.h"
#include "I2Cdev.h"
#include "hmc6352.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "t5403.h"
#include "sensors.h"
#include "imumaths.h"

/*
Open a port in your server with netcat and start listening
    % nc -lvp port number
And in the machine you are reading the serial port send it with netcat as root
    % nc ipaddress portnumber < /dev/ttyACM0
If you want to store the data in the server you can redirect the data to a text file. First create a file where you are saving the data
    % touch data.txt
And then start saving data
    % nc -lvp port number > logfile.txt
*/

#define LED_PIN 13 // (Arduino is 13)
const uint16_t sampleTimeMs = 500;
uint32_t thisSampleTimeMs = 0;	// Time in ms
#define SEPARATOR ","
#define TELEMETRY_SIGNATURE "1ACFFC1D"

Sensors sens;
bool blinkState = false;


imu::Quaternion qSensorAccRocket0;
imu::Quaternion qSensorAccRocket1;
imu::Quaternion qVelocityRocket0;
imu::Quaternion qVelocityRocket1;
imu::Quaternion qPositionRocket;

/*
imu::Quaternion sensorGyroRocket;     // Sensorernas orientering inuti raketen.
imu::Quaternion launchPosWorld;     // Referenshöjd. Noll är ?? meter under/över startplattan
imu::Quaternion launchOrientWorld;   // Kompassriktning, pekar uppåt
imu::Quaternion rocketPosWorld;     // Avvikelse från launchPos
imu::Quaternion rocketOrientWorld;  // Raketens riktning i det stora koordinatsystemet
imu::Quaternion sensorAltitudeWorld; // Sensorernas orientering inuti raketen.
imu::Quaternion sensorCompassRocket;  // Sensorernas orientering inuti raketen.

*/


uint16_t timeInSampleWindow( void )
{
  return (millis() % sampleTimeMs);
}


void waitFor( uint16_t triggerTime )
{
  if (triggerTime < sampleTimeMs)
  {
    while ( timeInSampleWindow() < triggerTime) 
    {
    }
  }
}

uint16_t delayTimeMs = 0;

#define Xaxis 0
#define Yaxis 1
#define Zaxis 2

void logSensorHeadingsFirstPart()
{
    Serial.print("Time [ms]");
    Serial.print(SEPARATOR); 
    Serial.print("Sample time [ms]");
    Serial.print(SEPARATOR); 
    Serial.print("Compass heading [deg]");
    Serial.print(SEPARATOR); 
    Serial.print("AccX [g]");
    Serial.print(SEPARATOR); 
    Serial.print("AccY [g]");
    Serial.print(SEPARATOR); 
    Serial.print("AccZ [g]");
    Serial.print(SEPARATOR); 
    Serial.print("RotX");
    Serial.print(SEPARATOR); 
    Serial.print("RotY");
    Serial.print(SEPARATOR); 
    Serial.print("RotZ");
    Serial.print(SEPARATOR); 
}


void logSensorValuesFirstPart(Sensors sens)
{
  Serial.print(millis());
  Serial.print(SEPARATOR); 
  Serial.print(thisSampleTimeMs);
  Serial.print(SEPARATOR); 

  // Log compass heading  
  Serial.print(sens.compassHeading / 10);
  Serial.print(SEPARATOR); 

  // Log acceleration
  Serial.print(sens.acceleration[Xaxis]);
  Serial.print(SEPARATOR); 
  Serial.print(sens.acceleration[Yaxis]); 
  Serial.print(SEPARATOR); 
  Serial.print(sens.acceleration[Zaxis]); 
  Serial.print(SEPARATOR); 

  // Log rotation
  Serial.print(sens.rotation[Xaxis]); 
  Serial.print(SEPARATOR); 
  Serial.print(sens.rotation[Yaxis]); 
  Serial.print(SEPARATOR); 
  Serial.print(sens.rotation[Zaxis]); 
  Serial.print(SEPARATOR); 
}

void logSensorHeadingsSecondPart()
{
    Serial.print("Temperature [C]");
    Serial.print(SEPARATOR); 
    Serial.print("Pressure [Pa]");
    Serial.print(SEPARATOR); 
    Serial.print("Altitude [m]");
    Serial.print(SEPARATOR); 
    Serial.print("Supply [V]");
}


void logSensorValuesSecondPart(Sensors sens)
{
  // Log temperature
  Serial.print(sens.temperatureCelsius / 100.0);
  Serial.print(SEPARATOR); 

  // Log pressure
  Serial.print(sens.pressure);
  Serial.print(SEPARATOR); 

  // Log altitude
  Serial.print(sens.altitudeMeter);
  Serial.print(SEPARATOR); 

  // Log supply voltage
  Serial.print(sens.supplyVoltage);
  Serial.print(SEPARATOR); 
}

void logQuaternionHeading(String s)
{
  Serial.print(s);
  Serial.print(" w");
  Serial.print(SEPARATOR); 
  Serial.print(s);
  Serial.print(" x");
  Serial.print(SEPARATOR); 
  Serial.print(s);
  Serial.print(" y");
  Serial.print(SEPARATOR); 
  Serial.print(s);
  Serial.print(" y");
  Serial.print(SEPARATOR); 
}


void logQuaternionValues(imu::Quaternion q)
{
  Serial.print(q.w());
  Serial.print(SEPARATOR); 
  Serial.print(q.x());
  Serial.print(SEPARATOR); 
  Serial.print(q.y());
  Serial.print(SEPARATOR); 
  Serial.print(q.z());
  Serial.print(SEPARATOR); 
  
}

void setup()
{
    // Initialize serial communication and identify ourselves
    Serial.begin(9600);
    Serial.println("Knasa Onboard Computer 1");

    // Initialize sensors
    Serial.println("Initializing I2C sensors.");
    sens.initialize();
    sens.calibrate(1);

    // configure LED for output
    pinMode(LED_PIN, OUTPUT);

    // Logging unique signature for the telemetry receiver to recognize
    Serial.println(TELEMETRY_SIGNATURE);
        
    // Logging headline for Excel and telemetry receiver
    logSensorHeadingsFirstPart();
    logSensorHeadingsSecondPart();

    logQuaternionHeading("Velocity");
    logQuaternionHeading("Position");
    Serial.println(); 
}

void loop()
{
  // Wait for sample window to start
  while ( timeInSampleWindow() != 0) 
  {
  }
  // Get absolute time of this sample window start
  thisSampleTimeMs = millis();

  delayTimeMs = timeInSampleWindow() + sens.acquisitions1Start();

  // Wait for sensors to perform measurements
  waitFor(delayTimeMs);

  // Get the raw data from the sensors
  sens.rawDataRetrieve1();

  // Start the next block of sensor acquisitions
  delayTimeMs += sens.acquisitions2Start();
  // Manage data from the first sensor acquisition block and log them
  sens.convertAndGet1();
  logSensorValuesFirstPart(sens);

  ///////////////////////////////////////////
  // Tröghetsnavigering
  ///////////////////////////////////////////
  qSensorAccRocket1 = imu::Quaternion(0,
                                   sens.acceleration[Xaxis] + 0.0,
                                   sens.acceleration[Yaxis] + 0.0,
                                   sens.acceleration[Zaxis] + 0.0);
  // Trapezoid Integral
  qVelocityRocket1 = qVelocityRocket0 + ( (qSensorAccRocket0 + qSensorAccRocket1) * (sampleTimeMs/2000.0) );

  qSensorAccRocket0 = imu::Quaternion(0, qSensorAccRocket1.x() + 0.0,
                                         qSensorAccRocket1.y() + 0.0,
                                         qSensorAccRocket1.z() + 0.0);


  // Trapezoid Integral. Delta movement in Rocket's coordinate system due to acceleration this sample period
  qPositionRocket = qPositionRocket + ( (qVelocityRocket0 + qVelocityRocket1) * (sampleTimeMs/2000.0) );

  qVelocityRocket0 = imu::Quaternion(0, qVelocityRocket1.x() + 0.0,
                                        qVelocityRocket1.y() + 0.0,
                                        qVelocityRocket1.z() + 0.0);
  Serial.print(" Vel: ");
  logQuaternionValues(qVelocityRocket0);
  Serial.print(" Pos: ");
  logQuaternionValues(qPositionRocket);


  
  ///////////////////////////////////////////
  // Wait for sensors to perform measurements
  ///////////////////////////////////////////
  waitFor(delayTimeMs);

  // Get the raw data from the sensors
  sens.rawDataRetrieve2();
  // Manage data from the second sensor acquisition block and log them
  sens.convertAndGet2();
  Serial.print(" 2: ");
  logSensorValuesSecondPart(sens);


  ///////////////////////////////////////////
  // Kalmanfiltrering
  ///////////////////////////////////////////


  Serial.print("  ");
  Serial.print(timeInSampleWindow()); 
  Serial.print(SEPARATOR); 

  // End of line
  // Serial.print(SEPARATOR); 
  Serial.println();

  
  // blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}
