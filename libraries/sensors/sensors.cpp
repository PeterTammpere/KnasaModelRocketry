/*
 * sensors.cpp
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
 
 #include "sensors.h"
 
 Sensors::Sensors()
 {
 }
 
 void Sensors::initialize()
 {
	// join I2C bus (I2Cdev library doesn't do this automatically)
	Wire.begin();

	// Gyro has a start-up time of 20 ms.
 	gyro.initialize();
 	gyro.setDLPFBandwidth(ITG3200_DLPF_BW_5);

 	// Compass has a wake-up time of < 1ms
	compass.wakeup();
 	
	// Accelerometer
 	accelerometer.initialize();
	accelerometer.setFullResolution(FULL_RESOLUTION_ON);	

	// Barometer
 	barometer.begin();
 	
 	// Voltmeter
 	// Nothing to do here
 	
 	delay(20);	// Gyro sets the delay here
 }

 
 void Sensors::calibrate( uint16_t numMeasurements)
 {
/* 	uint16_t i = 0;
	pressureRef = 0;
 	temperatureRef = 0;
*/

 	// Read reference altitude, zero acceleration and zero rotation
 	// calculate average
	compassHeadingRef = compass.getHeading();

	temperatureCelsiusRef = barometer.getTemperature(CELSIUS);

	pressureBase = barometer.getPressure(MODE_ULTRA);

/*
	for (i=0; i<numMeasurements; i++)
	{


		// Read pressure from the sensor in Pa. This operation takes about 
		// 67ms to complete in ULTRA_MODE.  Other Modes are available for faster, yet
		// less precise measurements.
		// MODE_LOW      = 5 ms
		// MODE_STANDARD = 11 ms
		// MODE_HIGH     = 19 ms
		// MODE_ULTRA    = 67 ms
	 	pressureRef += barometer.getPressure(MODE_HIGH);
	 	temperatureRef += barometer.getTempereature(CELSIUS);
 	}
 	pressureRef /= numMeasurements;
 	temperatureRef /= numMeasurements;
*/


 }
 

/*
void Sensors::sampleAllSensors()
{
	uint8_t i=0;
	double pressureRelative = 0;

	// Delay 6 ms
	compassHeading = compass.getHeading();
	
	// 
	accelerometer.getAcceleration(&accelerationRaw[0],
											&accelerationRaw[1],
											&accelerationRaw[2]);
	for (i=0; i<=2; i++)
	{
		acceleration[i] = accelerationRaw[i] * ACCELERATION_VALUE_CONVERT_TO_M_S2;
	}
	gyro.getRotation(	&rotation[0],
							&rotation[1],
							&rotation[2]);

  // Read temperature from the sensor in deg C. This operation takes about 
  // 4.5ms to complete.
  temperatureCelsius = barometer.getTemperature(CELSIUS);

  // Read pressure from the sensor in Pa. This operation takes about 
  // 67ms to complete in ULTRA_MODE.  Other Modes are available for faster, yet
  // less precise measurements.
  // MODE_LOW      = 5 ms
  // MODE_STANDARD = 11 ms
  // MODE_HIGH     = 19 ms
  // MODE_ULTRA    = 67 ms
  
  pressure = barometer.getPressure(MODE_ULTRA);
  
  // Convert abs pressure with the help of altitude into relative pressure
  // This is used in Weather stations.
  pressureRelative = sealevel(pressure, altitudeMeterBase);
  
  // Taking our baseline pressure at the beginning we can find an approximate
  // change in altitude based on the differences in pressure.   
  altitudeMeter = altitude(pressure , pressureBase);
	
	// It takes about 100 microseconds (0.0001 s) to read an analog input
	supplyVoltage = SUPPLY_12V_MEAS_CONV_VOLT * analogRead(SUPPLY_12V_MEAS_INPUT_PIN);
}

*/



uint8_t Sensors::acquisitions1Start(void)
// Returns delay time in ms
{
	uint8_t delayTimeMs = 0;
	delayTimeMs = MAX( delayTimeMs, barometer.acquisitionCommandTemperature() );
	delayTimeMs = MAX( delayTimeMs, compass.acquisitionCommandHeading() );
	return delayTimeMs;
}


void Sensors::rawDataRetrieve1(void)
{
	compass.rawDataRetrieveHeading();
	barometer.rawDataRetrieveTemperature();
	accelerometer.getAcceleration(&accelerationRaw[0],
											&accelerationRaw[1],
											&accelerationRaw[2]);
	gyro.getRotation(	&rotation[0],
							&rotation[1],
							&rotation[2]);

}


uint8_t Sensors::acquisitions2Start(void)
// Returns delay time in ms
{
	uint8_t delayTimeMs = 0;
	delayTimeMs = MAX( delayTimeMs, barometer.acquisitionCommandPressure(MODE_HIGH) );
	return delayTimeMs;
}


void Sensors::rawDataRetrieve2(void)
{
	barometer.rawDataRetrievePressure();
}


void Sensors::convertAndGet1(void)
{
	uint8_t i;
	compassHeading = compass.convertAndGetHeading();
	temperatureCelsius = barometer.convertAndGetTemperature(CELSIUS);
	for (i=0; i<=2; i++)
	{
		acceleration[i] = accelerationRaw[i] * ACCELERATION_VALUE_CONVERT_TO_M_S2;
	}

}


void Sensors::convertAndGet2(void)
{
	pressure = barometer.convertAndGetPressure();
	// Convert abs pressure with the help of altitude into relative pressure
	// This is used in Weather stations.
//	pressureRelative = sealevel(pressure, altitudeMeterBase);

	// Taking our baseline pressure at the beginning we can find an approximate
	// change in altitude based on the differences in pressure.   
	altitudeMeter = altitude(pressure , pressureBase);
	
	// It takes about 100 microseconds (0.0001 s) to read an analog input
	supplyVoltage = SUPPLY_12V_MEAS_CONV_VOLT * analogRead(SUPPLY_12V_MEAS_INPUT_PIN);
}



void Sensors::wakeup()
{
	compass.wakeup();
	delay(1); // Compass needs 100 us to wake up
}


void Sensors::sleep()
{
	compass.sleep();
}

void Sensors::check()
{
	// Check that compass measurement period is set correctly

	// Check that the accelerometer in X direction has a magnitude of 0.00 +/- ??
	// Check that the accelerometer in Y direction has a magnitude of 9.82 +/- ??
	// Check that the accelerometer in Z direction has a magnitude of 0.00 +/- ??

	// Check that all gyros are 0 +/- ??

	// Check that barometric altitude is 0 m +/- 2 meter

	// Check that supply voltage is within 12 +/- 1V range

}

// Thanks to Mike Grusin for the two functions below from the BMP180 example code. 
double Sensors::sealevel(double P, double A)
// Given a pressure P (Pa) taken at a specific altitude (meters),
// return the equivalent pressure (mb) at sea level.
// This produces pressure readings that can be used for weather measurements.
{
	return((P/100)/pow(1-(A/44330.0),5.255));
}


double Sensors::altitude(double P, double P0)
// Given a pressure measurement P (Pa) and the pressure at a baseline P0 (Pa),
// return altitude (meters) above baseline.
{
	return(44330.0*(1-pow(P/P0,1/5.255)));
}


