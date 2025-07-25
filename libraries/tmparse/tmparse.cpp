/*
 * tmparse.cpp
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
 
 #include "tmparse.h"
 
 TMparse::TMparse()
 {
 	fieldSeparator = ',';	// Default field separator is a comma
 	numFields = 0;
 	localCopy = "";
 	result = "";
 }

/*
TMparse::TMparse(	char dedicatedFieldSeparator );
{
	fieldSeparator = dedicatedFieldSeparator;
	numFields = 0;
 	localCopy = "";
 	result = "";
}
*/
 
void TMparse::parseThisString( const char* inputString )
{
	errorCode = TMparse_OK;
	uint16_t fieldIndex, len;

	// Nollställ alla fält
	for (fieldIndex=0; fieldIndex < MAX_NUM_FIELDS; fieldIndex++)
	{
		separatorPositions[fieldIndex] = ;
	}
	localCopy = inputString;		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	
	fieldIndex = 0;
	len = localCopy.length();
	pos = 0;

	errorCode = TMparse_WARNING_EMPTY_STRING;
	while (  (len > 0) &&
				(fieldIndex < MAX_NUM_FIELDS) )
	{
		pos = localCopy.indexOf( fieldSeparator, pos );
		if ( 	(pos < len) &&
				(pos >= 0) )
		{
			separatorPositions[fieldIndex] = pos;
			fieldIndex++;
			pos++;
		}
	}
	
}

String TMparse::getField( uint16_t fieldPosition)
{
	errorCode = TMparse_OK;
	uint16_t startPos = 0;
	uint16_t stopPos = localCopy.length();
	
	if ( (fieldPosition >= 0) &&
		  (fieldPosition < MAX_NUM_FIELDS) )
   {
   	if (fieldPosition > 0)
   	{
   		startPos = separatorPositions[fieldPosition-1]+1;
		}
		if (fieldPosition < numFields)
		{
			stopPos = separatorPositions[fieldPosition]-1;
		}
		result = localCopy.substring(startPos,stopPos);
  	}
  	else
  	{
	  	errorCode = TMparse_ERROR_INCORRECT_FIELD_POSITION;
	  	result = "?";
  	}
	return result;
}


