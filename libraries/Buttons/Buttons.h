/*
 * Buttons.h
 * 
 * Copyright (c) 2016 Peter Tammpere <peter.tammpere at gmail.com>. All rights reserved.
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
 
// Buttons
// Addons to handle buttons for the Liquid Crystal Display
//

#ifndef BUTTONS_H
#define BUTTONS_H


class Buttons
{
	public:

	Buttons();
	//Buttons(uint8_t inputPin);

	typedef enum buttonVal
	{
		UNDEFINED,
		UNPRESSED,
		SELECT,
		LEFT,
		RIGHT,
		UP,
		DOWN
	} buttonVal;

	Buttons::buttonVal analog2Button(int x);

	private:
	
};



#endif

