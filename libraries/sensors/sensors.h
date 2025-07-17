/*
 * sensors.h
 * 
 * Copyright (c) 2015 Peter Tammpere <peter.tammpere at gmail.com>. All rights reserved.
 * 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef sensors_h
#define sensors_h

// ************************************************************************* //
// I2C:

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"
// I2Cdev and ADXL345 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"


// ************************************************************************* //
// Compass:
#include "hmc6352.h"
 
// ************************************************************************* //
// Accelerometer:
#include "ADXL345.h"
#define FULL_RESOLUTION_ON 1 
// LSB = 4 mg = 0.03928 m/s2 = 39.28 mm/s2
#define ACCELERATION_VALUE_CONVERT_TO_M_S2 0.03928

 
// ************************************************************************* //
// Gyro:
#include "ITG3200.h"
 
// ************************************************************************* //
// Barometer:
#include "t5403.h"

// ************************************************************************* //
// Voltmeter:
// Use internal ADC plus some conversion.
#define SUPPLY_12V_MEAS_INPUT_PIN A0	// A0 is connected to voltage divider
#define SUPPLY_12V_MEAS_CONV_VOLT 1		// Conversion factor to get actual value

// ************************************************************************* //
#define MAX(A,B) (A>B ? A : B)
#define MIN(A,B) (A<B ? A : B)

 
class Sensors
{
	public:
	
		// All sensors:
		Sensors();
		void initialize();	// Initializes all sensors. Called at startup.
		
		void wakeup();		// Wakes up sensors from sleep. Includes sufficient delays
		void sleep();		// Puts sensors to sleep. No delays.
		void check();		// Checks that all sensors can be reached, status awake and correctly  configured.
		void selftest();	// Activates self-test procedures including delays.		

		void calibrate(uint16_t numMeasurements);	// Calibration procedure to acquire reference values and noise.
		void sampleAllSensors();						// Samples all sensors
		void sampleMotionSensors();					// Samples only accelerometer and gyro sensors
		uint32_t measWindowMillis = 0;				// Time difference between first and last measurement in ms
		uint32_t startTimeMillis = 0;					// Time at measurement start in ms


		uint8_t acquisitions1Start(void);
		uint8_t acquisitions2Start(void);
		void rawDataRetrieve1(void);
		void rawDataRetrieve2(void);
		void convertAndGet1(void);
		void convertAndGet2(void);

		
		// Compass:
		uint16_t compassHeading = 0;		// 10*degrees [0..3599]
		
		// Accelerometer:
		int16_t accelerationRaw[3] = {0,0,0};	// {x,y,z} raw from sensor
		double acceleration[3] = {0,0,0};		// {x,y,z} in m/s2
		
	
		// Gyro:
		int16_t rotation[3] = {0,0,0};
		
		// Barometer + Thermometer:
//		int16_t relativeAltitudeMeter = 0;
		double altitudeMeter = 0;
		double pressure = 0;
		double pressureRelative = 0;
		int16_t temperatureCelsius = 0;
		
		// Voltmeter
		double supplyVoltage = 0;
		
	private:
		// Compass sensor:
		HMC6352 compass;
		uint16_t compassHeadingRef;	// 10*degrees [0..3599] reference at calibration

		// Accelerometer:
		ADXL345 accelerometer;
		int16_t accelerationRef[3];	// {x,y,z} reference at calibration

		// Gyro:
		ITG3200 gyro;
		int16_t rotationRef[3];			// Reference rotation at calibration

		// Barometer + Thermometer:
		T5403 barometer; 								// barometer(MODE_I2C);
		int16_t temperatureCelsiusRef = 0;		// Reference temperature
		const double altitudeMeterBase = 10.0;	// Base altitude in Mölndal
		double pressureBase = 0;					// Base pressure before takeoff

		double altitudeMeterRef = 0;				// Reference altitude before takeoff
		double sealevel(double P, double A);
		double altitude(double P, double P0);
		
		// Voltmeter
		double supplyVoltageRef = 0;
		
};


#endif
