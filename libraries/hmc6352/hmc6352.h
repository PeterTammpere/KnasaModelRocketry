/*
 * hmc6352.h
 * 
 * Copyright (c) 2014 Peter Tammpere <peter.tammpere at gmail.com>. All rights reserved.
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
#ifndef hmc6352_h
#define hmc6352_h

#include "I2Cdev.h"
#include <Wire.h>


// Factory set I2C address
#define HMC6352_DEFAULT_ADDRESS					(0x42 >> 1)  // Drop R/W-bit

// I2C Commands
#define HMC6352_CMD_WRITE_EE						0x77	// w
#define HMC6352_CMD_READ_EE						0x72	// r
#define HMC6352_CMD_WRITE_RAM						0x47	// G
#define HMC6352_CMD_READ_RAM						0x67	// g
#define HMC6352_CMD_GOTO_SLEEP					0x53	// S
#define HMC6352_CMD_WAKE_UP						0x57	// W
#define HMC6352_CMD_UPDATE_BRIDGE_OFFSETS		0x4F	// O
#define HMC6352_CMD_ENTER_CALIB_MODE			0x43	// C
#define HMC6352_CMD_EXIT_CALIB_MODE				0x45	// E
#define HMC6352_CMD_SAVE_OPMODE					0x4C	// L
#define HMC6352_CMD_GET_HEADING					0x41	// A


// EEPROM Addresses
#define HMC6352_EE_I2C_ADDRESS 						0x00  // I2C slave address Def: 0x42
#define HMC6352_EE_MAGNETOMETER_X_OFFSET_MSB 	0x01  // Factory test value
#define HMC6352_EE_MAGNETOMETER_X_OFFSET_LSB 	0x02  //  - " -
#define HMC6352_EE_MAGNETOMETER_Y_OFFSET_MSB 	0x03  //  - " -
#define HMC6352_EE_MAGNETOMETER_Y_OFFSET_LSB 	0x04  //  - " -
#define HMC6352_EE_TIME_DELAY 						0x05  // Time Delay (0 – 255 ms) Def: 1
#define HMC6352_EE_NUM_OF_MEASUREMENTS				0x06  // (1-16) Def: 4
#define HMC6352_EE_SW_VERSION							0x07  // (>1)
#define HMC6352_EE_OPERATION_MODE_CTRL 			0x08  // Def: 0x50

// Bit fields for Operation Mode Control
#define HMC6352_OPMODE_MEAS_RATE_1_HZ		0x0
#define HMC6352_OPMODE_MEAS_RATE_5_HZ		0x1
#define HMC6352_OPMODE_MEAS_RATE_10_HZ		0x2
#define HMC6352_OPMODE_MEAS_RATE_20_HZ		0x3

#define HMC6352_OPMODE_PERIODIC_SR_OFF		0x0
#define HMC6352_OPMODE_PERIODIC_SR_ON		0x1

#define HMC6352_OPMODE_STANDBY_MODE			0x0
#define HMC6352_OPMODE_QUERY_MODE			0x1
#define HMC6352_OPMODE_CONTINUOUS_MODE		0x2

// RAM Addresses
#define HMC6352_RAM_OPERATION_MODE_CTRL	0x7F   // Copied from EEPROM to RAM at start (0x74!?)
#define HMC6352_RAM_OUTPUT_MODE				0x4E

// Bit field for Output Mode
#define HMC6352_OUT_HEADING_MODE					0x00
#define HMC6352_OUT_RAW_MAGNETOMETER_X_MODE	0x01
#define HMC6352_OUT_RAW_MAGNETOMETER_Y_MODE	0x02
#define HMC6352_OUT_MAGNETOMETER_X_MODE		0x03
#define HMC6352_OUT_MAGNETOMETER_Y_MODE		0x04


class HMC6352
{
	public:

		HMC6352();
		HMC6352(uint8_t writeAddress, uint8_t readAddress);
/*
		uint8_t getEeRegister(uint8_t eeRegisterAddress);
		void setEeRegister(uint8_t eeRegisterAddress, uint8_t value);
		void setEeRegisterOpmode(uint8_t mode, uint8_t period, uint8_t measRate);
		*/
		
		// ------------------------------------------------------------------- //
		// Compass Heading
		
		// Stepwise procedure
		// Step 1: Command sensor to start aquisition. Return delay in ms.
		uint8_t  acquisitionCommandHeading(void);
		// Step 2: Retrive sensor raw data and store in private variable.
		void rawDataRetrieveHeading(void);
		// Step 3: Provide heading data.
		uint16_t convertAndGetHeading( void );
		
		// Complete sequence - steps 1,2 and 3 including delays.
		uint16_t getHeading();
		void wakeup();
		void sleep();
		bool check();

  private:
		uint8_t devAddr;
		uint16_t headingValue = 0;
};


#endif
