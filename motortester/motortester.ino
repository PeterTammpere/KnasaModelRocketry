// KNASA Motortester

#define __G 9.82

//
// Load Cell
//
// #include </home/peter/sketchbook/libraries/HX711/HX711.h>
#include <HX711.h>
#define DOUT  3    // Blå
#define CLK  2     // Vit
HX711 scale(DOUT, CLK);

// Calibration weights
//#define CALIBRATION_WEIGHT_GRAMS (846)  // gram Plåtlåda med skruvdragare
//#define CALIBRATION_WEIGHT_GRAMS (1000) // gram 1kg kalibreringsvikt
//#define CALIBRATION_WEIGHT_GRAMS (1493) // gram Slägghammare
#define CALIBRATION_WEIGHT_GRAMS (1500)   // gram 1500g pepsicolaflaska

#define HX711_DEFAULT_CALIBRATION_FACTOR (210.14)  // For measurements in grams, gain 128
//#define HX711_DEFAULT_CALIBRATION_FACTOR (210.59)  // For measurements in grams, gain 128

#define HX711_GAIN_SETTING_1 (64)
#define HX711_GAIN_SETTING_2 (128)
#define NUM_MEASUREMENTS (20)


//
// LCD and Buttons
//
#include <LiquidCrystal.h>
#include </home/peter/sketchbook/libraries/LCD_utils/LCD_characters.h>
// #include </home/peter/sketchbook/libraries/LCD_utils/Buttons.h>
#include <Buttons.h>

//
// Utils
//
#define MAX(A,B) (A>B ? A : B)
#define MIN(A,B) (A<B ? A : B)

//
// Characters
//
#define SEPARATOR ','
CHARDEF_ARROW_UP;
CHARDEF_ARROW_DOWN;

//
// Global variables
//
Buttons knappar;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);   // initialize the library with the numbers of the interface pins
int sequenceNumber = 1;


//
//  Handle Menu Items to select from
//
#define MAX_ITEMS_MENU 4
#define MENU_TARE 0
#define MENU_CALIBRATE 1
#define MENU_RECORD 2
#define MENU_GAIN 3

char menuText[MAX_ITEMS_MENU][7] =
{ {"Tare  "}, // Zeroing the load cell
  {"Calib."}, // Calibrate the load cell using a known weight
  {"Record"}, // Start recording of model rocket engine
  {"Gain  "}  // Toggles between two gain factors
};
int selectedMenuItem = 0;

//
//  Handle values to display
//
#define MAX_ITEMS_VALUES 7
#define VALUE_WEIGHT 0
#define VALUE_FORCE 1
#define VALUE_IMPULSE 2
#define VALUE_PEAK_FORCE 3
#define VALUE_CAL_FACT 4
#define VALUE_GAIN 5
#define VALUE_WEIGHT_AVERAGE 6

float value[MAX_ITEMS_VALUES];
char valueText[MAX_ITEMS_VALUES][8] =
{
  {"Weight "},  // The load cell is used as a scale
  {"Force  "},  // The load cell is used as a dynamometer
  {"Impulse"},  // Reports resulting impulse from last measurement
  {"PkForce"},  // Reports resulting peak force from last measurement
  {"CalFact"},  // Reports the calibration factor used
  {"GainVal"},  // Reports the gain value used
  {"WeightA"}   // The load cell is used as an averaging scale
};
int selectedValue = 0;


// Tare
void doCommandTare( void )
{
  lcd.clear();
  lcd.print("Taring...");
  (void) scale.read();	// Perform a "NULL read" if gain has been set.
  scale.tare(NUM_MEASUREMENTS); //Get a baseline reading
}

// Calibrate
float doCommandCalibrate( const float calibrationWeightGrams )
{
  long measuredWeight = 0;
  lcd.clear();
  lcd.print("Calibrating...");
  lcd.setCursor(0,1);
  lcd.print(calibrationWeightGrams);
  lcd.print(" gram");
  scale.set_scale(1);
  (void) scale.read();	// Perform a "NULL read" if gain has been set.
  measuredWeight = scale.get_units(NUM_MEASUREMENTS);
  scale.set_scale(measuredWeight/calibrationWeightGrams);
  return measuredWeight/calibrationWeightGrams;
}


void printHeading( const int sequence)
{
  Serial.println();
  Serial.println("*** KNASA - Model Rocket Motor Test ***");
  
  Serial.print("Test sequence:      ");
  Serial.print(sequence);  
  Serial.println();
  
  Serial.print("Calibration factor: ");
  Serial.print(value[VALUE_CAL_FACT]);
  Serial.println();

  Serial.print("Gain value:         ");
  Serial.print(value[VALUE_GAIN]);
  Serial.println();

  Serial.println("***************************************");

  Serial.println();
  Serial.print("Time [ms]");
  Serial.print(SEPARATOR);
  Serial.print("Force [N]");
  Serial.print(SEPARATOR);
  Serial.print("Impulse [Ns]");
  Serial.print(SEPARATOR);
  Serial.println();
}

// Record
void doCommandRecord( float * const impulseResult,
                      float * const peakForceResult,
                      const int testSequence)
{
  unsigned long time1 = 0;
  unsigned long time2 = 0;
  unsigned long startTime = 0;
  float impulse = 0.0;
  float peakForce = 0.0;
  float force1 = 0.0;
  float force2 = 0.0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Recording... ");
  lcd.print(testSequence);
  while (knappar.analog2Button( analogRead(A0) ) != Buttons::UNPRESSED)
  {
  }
  
  force1 = ( __G * scale.get_units() )/1000;
  time1 = millis();
  startTime = time1;
  if ( abs(force1) > abs(peakForce) )
  {
    peakForce = force1;
  }

  printHeading( testSequence );
  
  while (knappar.analog2Button( analogRead(A0) ) != Buttons::SELECT)
  {
    Serial.print(time1-startTime);
    Serial.print(SEPARATOR);
    Serial.print(force1);
    Serial.print(SEPARATOR);
    Serial.print(impulse / 1000);
    Serial.println();
    lcd.setCursor(0,1);
    lcd.print(time1-startTime);
    lcd.setCursor(8,1);
    lcd.print(force1);
    force2 = ( __G * scale.get_units() )/1000;
    time2 = millis();
    impulse += (time2 - time1) * (force1 + force2) / 2;
    time1 = time2;
    force1 = force2;
    if ( abs(force1) > abs(peakForce) )
    {
      peakForce = force1;
    }
  }
    Serial.print(time1-startTime);
    Serial.print(SEPARATOR);
    Serial.print(force1);
    Serial.print(SEPARATOR);
    Serial.print(impulse / 1000);
    Serial.println();
    
    *impulseResult = impulse/1000;
    *peakForceResult = peakForce;

}


float doCommandGain ( const float presentGain )
{
  float newGain = HX711_GAIN_SETTING_1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set new Gain to: ");
  if ( presentGain == HX711_GAIN_SETTING_1 )
  {
    newGain = HX711_GAIN_SETTING_2;
  }
  lcd.setCursor(0,1);
  lcd.print(newGain);
  delay(500);
  return newGain;
}


#define NUM_AVERAGING_BUCKETS 50
float bucket[ NUM_AVERAGING_BUCKETS ];
int freeBucketIndex = 0;

void resetAveragingBuckets ( void )
{
  int i = 0;
  for ( i = 0; i < NUM_AVERAGING_BUCKETS ; i++ )
  {
    bucket[ i ] = 0.0;
  }
}

float nextAverageValue( const float newValue )
{
  float sum = 0.0;
  float average = 0.0;
  int i = 0;
  if ( (freeBucketIndex >= 0) && (freeBucketIndex < NUM_AVERAGING_BUCKETS ) )
  {
    bucket[ freeBucketIndex ] = newValue;
    for ( i=0 ; i < NUM_AVERAGING_BUCKETS; i++)
    {
      sum = sum + bucket[ i ];
    }
    average = sum / NUM_AVERAGING_BUCKETS; // Make this value an average value
    freeBucketIndex++;
    if ( freeBucketIndex >= NUM_AVERAGING_BUCKETS )
    {
      freeBucketIndex = 0;
    }
    return average;
  }
  else
  {
    return 0.0; /// FEL!!
  }
}


////////////////////////////////////////////////////////////////////////////////
void setup()
{
  int i;
  CHARCREATE_ARROW_UP;
  CHARCREATE_ARROW_DOWN;
  
  lcd.begin(16, 2);                      // set up the LCD's number of columns and rows
  lcd.clear();                           // Clear LCD
  lcd.setCursor(0,0);
  lcd.print("KNASA | LoadCell");
  lcd.setCursor(0,1);
  lcd.print("* Motor tester *");
  
  // Logging
  Serial.begin(9600);

  // Load Cell default values
  value[VALUE_GAIN] = HX711_GAIN_SETTING_2;
  value[VALUE_CAL_FACT] = HX711_DEFAULT_CALIBRATION_FACTOR;
  scale.set_gain( (int) int( value[VALUE_GAIN] ) );
  scale.set_scale( value[VALUE_CAL_FACT] );
  scale.tare( NUM_MEASUREMENTS );

  delay(500);
  lcd.clear();
};


////////////////////////////////////////////////////////////////////////////////
void loop()
{ 


  lcd.setCursor (0,0);
  lcd.print (valueText[selectedValue]);
  lcd.print (" ");
  lcd.print (value[selectedValue]);
  lcd.print ("        ");
  
  lcd.setCursor (0,1);
  lcd.print ("Menu ");
  lcd.print (CHAR_ARROW_UP);
  lcd.print ("/");
  lcd.print (CHAR_ARROW_DOWN);
  lcd.print (" ");
  lcd.print (menuText[selectedMenuItem]);


  // Select according to pressed button
  switch ( knappar.analog2Button( analogRead(A0) ) )
  {
    case Buttons::RIGHT:
      selectedValue++;
      if (selectedValue > MAX_ITEMS_VALUES-1)
      {
        selectedValue = 0;
      }  
      break;

    case Buttons::LEFT:
      selectedValue--;
      if (selectedValue < 0)
      {
        selectedValue = MAX_ITEMS_VALUES-1;
      }  
      break;

    case Buttons::DOWN:  
      selectedMenuItem++;
      if (selectedMenuItem > MAX_ITEMS_MENU-1)
      {
        selectedMenuItem = 0;
      }
      break;

    case Buttons::UP:
      selectedMenuItem--;
      if (selectedMenuItem < 0)
      {
        selectedMenuItem = MAX_ITEMS_MENU-1;
      }
      break;

    case Buttons::SELECT:
      switch(selectedMenuItem)
      {
        case MENU_TARE:
          doCommandTare();
          break;

        case MENU_CALIBRATE:
          value[VALUE_CAL_FACT] = doCommandCalibrate(CALIBRATION_WEIGHT_GRAMS);
          break;

        case MENU_RECORD:
          doCommandRecord( &value[VALUE_IMPULSE],
                           &value[VALUE_PEAK_FORCE],
                           sequenceNumber++);
          break;

        case MENU_GAIN:
          value[VALUE_GAIN] = doCommandGain( value[VALUE_GAIN] );
          break;

        default:
          break;  
      }
      break;
    default:
      break;
  }

  // Buttons shall be released
  while (knappar.analog2Button( analogRead(A0) ) != Buttons::UNPRESSED)
  {
  }
  value[VALUE_WEIGHT] = scale.get_units();
  value[VALUE_FORCE]  = (value[VALUE_WEIGHT] * __G )/ 1000;
  value[VALUE_WEIGHT_AVERAGE] = nextAverageValue( value[VALUE_WEIGHT] );
};

