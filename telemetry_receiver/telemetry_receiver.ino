// Telemetry data receiver for Knasa OBC1

// include the library code:
#include <LiquidCrystal.h>

// #include "tmparse.h"

#define SEPARATOR ','
#define TELEMETRY_SIGNATURE "1ACFFC1D"

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
#define CHAR_X_TAK char(248)
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

#define MAX(A,B) (A>B ? A : B)
#define MIN(A,B) (A<B ? A : B)

// Global variables
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);   // initialize the library with the numbers of the interface pins
//TMparse heading;
//TMparse tmData;
//uint8_t field = 0;

void setup()
{
  int i;
  lcd.begin(16, 2);                      // set up the LCD's number of columns and rows
  lcd.clear();                           // Clear LCD
  lcd.setCursor(0,0);                    // Set cursor to x=0 and y=0
  lcd.print("Knasa| Telemetry");         // Print text on LCD
  lcd.setCursor(0,1);

  for (i=0; i<5; i++)
  {
    lcd.setCursor(i,1);
    lcd.print(CHAR_STRIPES);
  }
  lcd.print("| Decoder");
  
  while (1)
  {}
  for (i=0; i<5; i++)
  {
    lcd.setCursor(i,1);
    lcd.print(CHAR_WHITE);
    delay(500);
  }  
  for (i=0; i<5; i++)
  {
    lcd.setCursor(i,1);
    lcd.print(" ");
    delay(500);
  }  
  lcd.clear();
  // Invänta TM synk

  // Läs in rubrikerna
//  heading.parseThisString("Time [ms],Sample time [ms],Compass heading [0.1 deg],AccX [g],AccY [g],AccZ [g],RotX,RotY,RotZ,Temperature [C],Pressure [Pa],Altitude [m],Supply [V]");
//  tmData.parseThisString("209,200,256,10.61,0.94,-1.18,18,36,-26,18,99939.00,-0.76,395.00,20");
};


void loop()
{ 
/*  int x;
  x = analogRead (0);                  // Read the analog value for buttons
  lcd.setCursor(0,1);

  if (x < 50)
  {                       // Right button is pressed
    lcd.print (CHAR_RIGHT_ARROW);
  }
  else if (x < 150)
  {                  // Up button is pressed
    lcd.print (CHAR_HAT);
    field = MIN(field+1, MAX_NUM_FIELDS-1);
  }
  else if (x < 300)
  {                   // Down button is pressed
    lcd.print ("v"); 
    field = MAX(field-1, 0);
  }
  else if (x < 500)
  {                   // Left button is pressed
    lcd.print (CHAR_LEFT_ARROW);
  }
  else if (x < 800)
  {                   // Select button is pressed
    lcd.print (CHAR_WHITE); 
  }

  lcd.print(field);
  lcd.print(":");
  lcd.print(tmData.getField(field));
  lcd.setCursor(0,1);
  lcd.print(heading.getField(field));
*/
}

