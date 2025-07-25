/*
 * tmparse.h
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
 
 
#ifndef tmparse_h
#define tmparse_h

#define MAX_NUM_FIELDS 20

typedef
	enum TMparseErrorCodes
	{
		TMparse_OK,
		TMparse_WARNING_EMPTY_STRING,
		TMparse_ERROR_INCORRECT_FIELD_POSITION,
		TMparse_WARNING_UNEXPECTED_NUMBER_OF_FIELDS,
		TMparse_ERROR_TOO_MANY_FIELDS
	} TMparseErrorCode_t;

// ************************************************************************* //


class TMparse
{
	public:
		TMparse();
//		TMparse(	char dedicatedFieldSeparator );
		
		// Separates a string into fields
		void parseThisString( const char* inputString );

		// Container of fields
		uint16_t numFields;
		String getField( uint16_t fieldPosition);
		String result;

		// Latest error code
		TMparseErrorCode_t errorCode = TMparse_OK;
	private:
		char fieldSeparator;
		String localCopy;
		uint8_t separatorPositions[MAX_NUM_FIELDS];
};
	

#endif
