/******************************************************************************
t5403.h
Library for T5403 barometric pressure sensor.
Casey Kuhns @ SparkFun Electronics
2/12/2014
https://github.com/sparkfun/T5403_Barometric_Breakout

The T5403 by Epcos is a low cost I2C barometric pressure sensor.  This sensor 
can be used in weather stations and for altitude estimations.  In this file are
the prototype functions in the T5400 class

Resources:
This library uses the Arduino Wire.h to complete I2C transactions.

Development environment specifics:
	IDE: Arduino 1.0.5
	Hardware Platform: Arduino Pro 3.3V/8MHz
	T5403 Breakout Version: 1.0

NOTE:  SPI is currently unsupported in the hardware.  If a release comes with
hardware support this file will be updated.  All reference to SPI is currently
a place holder for future development.

This code is beerware. If you see me (or any other SparkFun employee) at the
local pub, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

#ifndef t5403_h
#define t5403_h

#include "Arduino.h"

// The T5403 is designed to function over both I2C or SPI. This library supports
// both. The interface mode used must be sent to the T5403 constructor. Use
// one of these two as the first parameter of the constructor.
enum interface_mode
{
	MODE_SPI,
	MODE_I2C,
};

// Define units for conversions. 
enum temperature_units
{
	CELSIUS,
	FAHRENHEIT,
};

// Device Address
#define T5403_I2C_ADDR	0x77
	
// Register addresses for operations
#define T5403_COMMAND_REG	0xF1
#define T5403_DATA_REG		0xF5

// Register addresses for calibration constants
#define T5403_C1		0x8E
#define T5403_C2		0x90
#define T5403_C3		0x92
#define T5403_C4		0x94
#define T5403_C5		0x96
#define T5403_C6		0x98
#define T5403_C7		0x9A
#define T5403_C8		0x9C

// definitions for pressure reading commands with accuracy modes
#define MODE_LOW			0x00
#define MODE_STANDARD	0x01
#define MODE_HIGH			0x10
#define MODE_ULTRA		0x11

// definition for temperature reading command
#define COMMAND_GET_TEMP	0x03

class T5403
{
	public:
		// Select the interface to be used in communication
		T5403();
		T5403(interface_mode interface);

		// Collect constants from sensor for calculations
		void begin(void);

		//	------------------------------------------------------------------- //
		// Temperature
		//
		// Stepwise procedure to get temperature.
		// Useful in time critical applications avoiding idle delays
		
		// Step 1:	Command the sensor to start temperature acquisition.
		// 			Returns required delay in ms.
		uint8_t acquisitionCommandTemperature(void);
	
		// Step 2:	Retrieve the raw sensor data and store in private variable
		void rawDataRetrieveTemperature(void);

		// Step 3:	Convert raw sensor data to useful unit
		int16_t convertAndGetTemperature(temperature_units units);

		// Complete sequence including idle delays to get temperature.
		// Returns calculated temperature.
		int16_t getTemperature(temperature_units units);

		//	------------------------------------------------------------------- //
		// Pressure
		//
		// Stepwise procedure to get pressure (and temperature).
		// Useful in time critical applications avoiding idle delays

		// Steps 1 and 2 from above are also needed here.

		// Step 3:	Command the sensor to start pressure acquisition.
		// 			Returns required delay in ms.
		uint8_t acquisitionCommandPressure(uint8_t commanded_precision);

		// Step 4:	Retrieve the raw sensor data and store in private variable
		void rawDataRetrievePressure(void);

		// Step 5:	Convert raw temperature and pressure data to useful pressure
		int32_t convertAndGetPressure( void );

		// Complete sequence 1-5 including idle delays to get temperature and
		// pressure. Returns calculated pressure from sensor.
		// Complete sequence with delays.
		int32_t getPressure(uint8_t precision);
		
		
	private:
		// Variable used to store interface selected for communication.
		interface_mode _interface; 

		// Raw input data from sensor
		int16_t temperature_raw; 
		uint16_t pressure_raw;

		// Constants filled in with T5403();
		uint16_t c1, c2, c3, c4;		
		int16_t c5, c6, c7, c8;
		
		// General delay function.  If delay() is not supported on other 
		// platforms it may be necessary to modify this function.
		// The units for sensorWait() are in ms. 
		void sensorWait(uint8_t time);
		
		// Communication transport functions. These can be modified to allow the 
		// library to work with other platforms and architectures.
		void communicationBegin();
		int8_t getData(uint8_t location, int16_t* output);
		int8_t sendCommand(uint8_t location, uint8_t command);

};

#endif
