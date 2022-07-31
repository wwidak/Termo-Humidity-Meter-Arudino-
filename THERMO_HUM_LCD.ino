//Wojciech Widak 2021

//www.elegoo.com
//2016.12.9

/*

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 */

// include the library code:
#include <LiquidCrystal.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

//Defining what pin Arudino LED is connected to in this case pin 13.

int ledPin = 13;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

void setup() {

  //Initialise serial port for Serial Monitor data display

  Serial.begin( 9600);
   
  //initialize pins as outputs

  pinMode (ledPin, OUTPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(9, 2);
  
  // for hum & temp sensor
  Serial.begin( 9600);
}

// for hum & temp sensor
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }
  return( false );
}


void loop() {

  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity ) == true )
  {
    Serial.print( "T = " );
    Serial.print( temperature, 1 );
    Serial.print( " deg. C, H = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );
    
    lcd.setCursor(4, 0);
    
    lcd.print( "T = " );
    lcd.print( temperature, 1 );

    lcd.setCursor(4, 1);
    
    lcd.print( "H = " );
    lcd.print( humidity, 1 );

    // Turning LED on (high)
  
    digitalWrite(ledPin, HIGH);
  
    // Wait time in miliseconds
    delay(1000);

    // Turning LED off (low)
    digitalWrite(ledPin, LOW);

    delay(3000);
  }

}
