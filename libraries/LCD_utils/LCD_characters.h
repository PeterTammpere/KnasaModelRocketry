/*
 * LCD_characters.h
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
 
// LCD_characters
// Addons to the LiquidCrystal library
//

#ifndef LCD_CHARACTERS_H
#define LCD_CHARACTERS_H

//---------------------------------------------------
// LCD character definitions
//---------------------------------------------------

// Greek characters
#define CHAR_ALFA char(224)
#define CHAR_AE char(225)
#define CHAR_BETA char(226)
#define CHAR_EPSILON char(227)
#define CHAR_MU char(228)
#define CHAR_SIGMA char(229)
#define CHAR_RHO char(230)
#define CHAR_OE char(239)
#define CHAR_THETA char(242)
#define CHAR_OMEGA char(244)
#define CHAR_UU char(245)
#define CHAR_SIGMA_V char(246)
#define CHAR_PI char(247)

// Math and Special char
#define CHAR_X_HAT char(248)
#define CHAR_DIVIDE char(253)
#define CHAR_GRAVE_ACCENT char(96)
#define CHAR_GRAVE_ACCENT_LOW char(164)

// Graphic
#define CHAR_STRIPES char(0)
#define CHAR_MINUS_LONG char(176)
#define CHAR_WHITE char(255)
#define CHAR_SQUARE char(219)

#define CHAR_HAT char(94)
#define CHAR_RIGHT_ARROW char(126)
#define CHAR_LEFT_ARROW char(127)

#define CHAR_DOT_MIDDLE char(165)
#define CHAR_RING_LOW char(161)
#define CHAR_RING_HIGH char(223)

// Special

#define CHAR_BAR_1 char(1)
#define CHARDEF_BAR_1 byte _char_bar_1[8] = {B10000,B10000,B10000,B10000,B10000,B10000,B10000,B10000}
#define CHARCREATE_BAR_1 lcd.createChar(1, _char_bar_1)

#define CHAR_BAR_2 char(2)
#define CHARDEF_BAR_2 byte _char_bar_2[8] = {B10100,B10100,B10100,B10100,B10100,B10100,B10100,B10100 }
#define CHARCREATE_BAR_2 lcd.createChar(2, _char_bar_2)

#define CHAR_BAR_3 char(3)
#define CHARDEF_BAR_3 byte _char_bar_3[8] = {B10101,B10101,B10101,B10101,B10101,B10101,B10101,B10101 }
#define CHARCREATE_BAR_3 lcd.createChar(3, _char_bar_3)


#define CHAR_ARROW_UP char(6)
#define CHARDEF_ARROW_UP byte _char_arrow_up[8] = {B00000,B00100,B01110,B10101,B00100,B00100,B00000,B00000}
#define CHARCREATE_ARROW_UP lcd.createChar(6, _char_arrow_up)

#define CHAR_ARROW_DOWN char(7)
#define CHARDEF_ARROW_DOWN byte _char_arrow_down[8] = {B00000,B00000,B00100,B00100,B10101,B01110,B00100,B00000 }
#define CHARCREATE_ARROW_DOWN lcd.createChar(7, _char_arrow_down)


//
//  Print a graphic bar, going left to right
//
/*void printBar(  int barSizeChars,
                int minValue,
                int maxValue,
                int value)
{
  int smallBar = 0;
  int largeBar = 0;
  int i = 0;
  float bar = 0.0;
  
  if ( (barSizeChars > 1) &&
       (barSizeChars <= 16) )
  {
    if ( (value >= minValue) &&
         (value <= maxValue) )
    {
      
      bar = value / (maxValue - minValue + 1);
      largeBar = barSizeChars * bar;
      if ( (largeBar > 0) &&
           (largeBar <= barSizeChars) )
      {
        for  ( i=0; largeBar; i++)
        {
          lcd.print (CHAR_BAR_3);
        }
      }
      smallBar = (barSizeChars * 3) * bar;
      smallBar = smallBar % 3;
      switch (smallBar)
      {
        case 1:
          lcd.print (CHAR_BAR_1);
          break;
        case 2:
          lcd.print (CHAR_BAR_2);
          break;
        default:
        break;
      }
    }
  }       
}  

*/


#endif

