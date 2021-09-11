/*  Program to control fairy lights
 *  Relay 230V
 *  RTC I2C
 *  Arduino 5V
 *  Turn on by LOW
 *  
 *  Last update 30-12-2019
 */


#include "lights.h"
#include <Wire.h>
#include "RTClib.h" // Real time clock
RTC_DS3231 RTC;

bool on_off = false; // State of the light

int hours, minutes, sec, day_n, mon_n, year_n; // Time variables

void readTime(){
  DateTime now = RTC.now();// Getting the current Time and storing it into a DateTime object

  hours = now.hour();
  minutes = now.minute();
  sec = now.second();

  day_n = now.day();
  mon_n = now.month();
  year_n = now.year();
}

// Turn on/off lights on time
void setBool(){
  if (hours == 16 && minutes == 0) on_off = true; // Turn on at 16:00
  if ((hours == 23 && minutes == 0) && !(day_n == 24 && mon_n == 12)) on_off = false;  // Turn off at 23:00 if today is 24.12
  if ((day_n == 25 && mon_n == 12) && (hours == 2 && minutes == 0)) on_off = false; // Turn off if 2:00 if today is 25.12 (night after 24.12)
}


void setup()
{
  // Turn off diode at pin no. 13 (to save energy)
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // Controller pin 12
  // Turn on by low but now turn it off (it's default)
  Lights lights = Lights(12, LOW);

  // Init RTC
  Wire.begin();
  RTC.begin();

  readTime();

  //teset
  Serial.begin(9600);
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.print(sec);
  Serial.print("_");
  Serial.println(day_n);
  Serial.end();
  
  // following line sets the RTC to the date & time this sketch was compiled
  // RTC.adjust(DateTime(__DATE__, __TIME__)); // Uncomment to set the clock
}
void loop()
{
  // Get time now
  readTime();

  
   /*/ test
  if(hours == 18)
    on_off = true;*/
/*
    // test 
    Serial.print(hours);
    Serial.print(":");
    Serial.print(minutes);
    Serial.print(":");
    Serial.print(sec);
    Serial.print("_");
    Serial.println(day_n);
    //Serial.println(minutes);
*/

  // Turn on every day in December
  if (day_n >= 24 && mon_n == 12) {
    setBool();
  }

  // Turn on every day until 06.01 (Three Kings' Day)
  // Then only wheekends
  // !!!In this version it is necessary to SET IT MANUALLY!!!
  if ((day_n < 7 || day_n == 12 || day_n == 11 || day_n == 19 || day_n == 18 || day_n == 25 || day_n == 26) && mon_n == 1) {
    setBool();
  }

  // Set the relay state
  // The state is invertet because lights are ON if controller pin is set as LOW
  digitalWrite(12, !on_off);

  delay(12000); // change if doesn't work
}
