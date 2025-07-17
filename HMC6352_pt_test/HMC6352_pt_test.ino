/*
 * hmc6352example.pde
 * 
 * Copyright (c) 2009 Ruben Laguna <ruben.laguna at gmail.com>. All rights reserved.
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

#include <Wire.h>
#include <I2Cdev.h>
#include <hmc6352.h>


//set up hmc6352
HMC6352 myHmc6352;
uint16_t heading;
  
void setup()
{  
  Serial.begin(38400);
  delay(100); 
  
  Serial.print("RST\r\n");delay(100);  
  myHmc6352.wakeup();
  delay(1);

}
/*
void readRegAndPrint( uint8_t reg)
{
  uint8_t val = 0;
  val = myHmc6352.getEeRegister(reg);
  Serial.print(reg);
  Serial.print(" = ");
  Serial.println(val);
}
*/
void loop() 
{ 
  delay(100);
  
 
/*  a = myHmc6352.getEeRegister(HMC6352_EE_I2C_ADDRESS);
  Serial.print(a);*/

//  myHmc6352.sleep();
 
  
/*  
  readRegAndPrint(HMC6352_EE_I2C_ADDRESS);
  readRegAndPrint(HMC6352_EE_MAGNETOMETER_X_OFFSET_MSB);
  readRegAndPrint(HMC6352_EE_MAGNETOMETER_X_OFFSET_LSB);
  readRegAndPrint(HMC6352_EE_MAGNETOMETER_Y_OFFSET_MSB);
  readRegAndPrint(HMC6352_EE_MAGNETOMETER_Y_OFFSET_LSB);
  readRegAndPrint(HMC6352_EE_TIME_DELAY);
  readRegAndPrint(HMC6352_EE_NUM_OF_MEASUREMENTS);
  readRegAndPrint(HMC6352_EE_SW_VERSION);
  readRegAndPrint(HMC6352_EE_OPERATION_MODE_CTRL);
  */

  heading = myHmc6352.getHeading();
  Serial.print(heading);
  Serial.print("\r\n");
  
}
