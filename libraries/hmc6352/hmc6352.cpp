/*
 * hmc6352.cpp
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
#include "hmc6352.h"
#include <Wire.h>
#include <I2Cdev.h>

#define HMC6352_DEFAULT_TIMEOUT 1000

HMC6352::HMC6352()
{
    devAddr = HMC6352_DEFAULT_ADDRESS;
    Wire.begin();
}

HMC6352::HMC6352(uint8_t writeAddress, uint8_t readAddress)
{
    devAddr = writeAddress;
    Wire.begin();
}

uint8_t  HMC6352::acquisitionCommandHeading(void)
{
	Wire.beginTransmission(devAddr);
	Wire.write( (uint8_t) HMC6352_CMD_GET_HEADING);
	Wire.endTransmission();
	
	return 6; // The HMC6352 needs 6 ms delay

}


void HMC6352::rawDataRetrieveHeading(void)
{
	uint8_t headingData[2] = {0, 0};
	uint16_t i=0;
	 
	Wire.beginTransmission(devAddr);
	// Request the 2 byte heading (MSB comes first)
	Wire.requestFrom(devAddr, (uint8_t) 2);
	i = 0;
	while(Wire.available() && i < 2)
	{
	headingData[i] = Wire.read();
		i++;
	}
	// Put the MSB and LSB together
	headingValue = (headingData[0] << 8) + headingData[1];
}

uint16_t HMC6352::convertAndGetHeading( void )
{
	return headingValue;
}

uint16_t HMC6352::getHeading(void)
{
	delay( acquisitionCommandHeading() );
	rawDataRetrieveHeading();
	return convertAndGetHeading();
}



/*
uint8_t HMC6352::getRegister(uint8_t memMode, uint8_t eeRegisterAddress)
{
   uint8_t data = 0;

	Wire.beginTransmission( devAddr );
	Wire.write( memMode );
	Wire.write( eeRegisterAddress );
	Wire.endTransmission();

	Wire.beginTransmission( devAddr);
	Wire.requestFrom( devAddr, 1); // Request 1 byte
	data = Wire.read();
	Wire.endTransmission();
	return data;
}


uint8_t HMC6352::getEeRegister(uint8_t eeRegisterAddress)
{
	return HMC6352::getRegister( HMC6352_CMD_READ_EE, eeRegisterAddress );
}

uint8_t HMC6352::getRamRegister(uint8_t ramRegisterAddress)
{
	return HMC6352::getRegister( HMC6352_CMD_READ_RAM, ramRegisterAddress );
}


void HMC6352::setRegister(uint8_t memMode,
							uint8_t eeRegisterAddress,
							uint8_t value)
{
	Wire.beginTransmission( devAddr );
	Wire.write( memMode );
	Wire.write( eeRegisterAddress );
	Wire.write( value );
	Wire.endTransmission();
}



void HMC6352::setEeRegister(uint8_t eeRegisterAddress, uint8_t value)
{
	HMC6352::setRegister(HMC6352_CMD_WRITE_EE, eeRegisterAddress, value);
}

void HMC6352::setRamRegister(uint8_t ramRegisterAddress, uint8_t value)
{
	HMC6352::setRegister(HMC6352_CMD_WRITE_RAM, ramRegisterAddress, value);
}
void HMC6352::setRamRegisterOpmode(uint8_t mode, uint8_t period, uint8_t measRate)
{
	setRamRegister( 
}
*/


void HMC6352::wakeup()
{
    bool status = I2Cdev::writeByte(
			devAddr,
			HMC6352_CMD_WAKE_UP,
			0);
}


void HMC6352::sleep()
{
    bool status = I2Cdev::writeByte(
			devAddr,
			HMC6352_CMD_GOTO_SLEEP,
			0);
}

