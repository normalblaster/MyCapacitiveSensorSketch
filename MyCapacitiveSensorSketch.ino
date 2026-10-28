#include <CapacitiveSensor.h>

#define LED_EXTERN 7
#define LED_EXTERN2 8
#define THRESHOLD 2000
bool bPrevTouched = false;
int iOn = LOW;
int iFlash = LOW;
int iLoopCount = 0;
int iFlashPeriod = 250;
/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

void setup()                    
{
   // Leave the auto calibrate at the default 20 second intervals
   //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   cs_4_2.set_CS_AutocaL_Millis(20000);
   Serial.begin(9600);

   pinMode( LED_EXTERN , OUTPUT );
   pinMode( LED_EXTERN2 , OUTPUT );
   pinMode( LED_BUILTIN , OUTPUT );

   iLoopCount = 0;
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(255);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.println(total1);                  // print sensor output 1

    bool bTouched = total1 > THRESHOLD;

    if( bTouched == false && bPrevTouched == true )
    {
        iOn = iOn == HIGH ? LOW : HIGH;
        digitalWrite(LED_EXTERN, iOn);
        delay(50);
    }

    bPrevTouched = bTouched;
    // arbitrary delay to limit data to serial port 
    iLoopCount ++;
    iFlash = iLoopCount > iFlashPeriod ? !iFlash : iFlash;
    iLoopCount = iLoopCount  > iFlashPeriod ? 0 : iLoopCount;
    digitalWrite( LED_BUILTIN , iFlash );
    digitalWrite( LED_EXTERN2 , iFlash );
}




