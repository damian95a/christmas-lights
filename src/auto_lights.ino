/*  Program to control christmas lights
 *  Relay 230V - turning on by LOW
 *  RTC I2C
 *  Arduino 5V
 */


#include "lights.h"
#include "calendar.h"
#include <Wire.h>
#include "RTClib.h" // Real time clock
RTC_DS3231 RTC;

bool on_off = false; // State of the light

int hours, minutes, sec, day_n, mon_n, year_n; // Time variables

// Controller pin 12
// Turn on by low but now turn it off (it's default state)
Lights lights_ctrl = Lights(12, LOW);
Calendar<short> cal = Calendar<short>(2021,4);



void readTime();
void lState(); // Turn on/off lights on time
void print_tim(); // debug

void setup()
{
  cal.fill_cal();
  cal.print_cal();
  // Turn off diode at pin no. 13 (to save energy)
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // Init RTC
  Wire.begin();
  RTC.begin();

  readTime();

  // debug
  //print_tim();
  
  // following line sets the RTC to the date & time this sketch was compiled
  //RTC.adjust(DateTime(__DATE__, __TIME__)); // Uncomment to set the clock
}

void loop()
{
  // Get time now
  readTime();

  
   /* //test
  if(hours == 18)
    on_off = true;*/


  // Turn on every day in December
  if (day_n >= 24 && mon_n == 12) {
    lState();
  }

  // Turn on every day until 06.01 (Three Kings' Day)
  // Then only wheekends
  // !!!In this version it is necessary to SET IT MANUALLY!!!
  if ((day_n < 7 || day_n == 12 || day_n == 11 || day_n == 19 || day_n == 18 || day_n == 25 || day_n == 26) && mon_n == 1) {
    lState();
  }


  delay(12000); // change if doesn't work
}





void readTime(){
  DateTime now = RTC.now();// Getting the current Time and storing it into a DateTime object

  hours = now.hour();
  minutes = now.minute();
  sec = now.second();

  day_n = now.day();
  mon_n = now.month();
  year_n = now.year();
}

void lState(){
  // Turn on/off lights on time
  if (hours == 16 && minutes == 0) lights_ctrl.turn_on(); // Turn on at 16:00
  if ((hours == 23 && minutes == 0) && !(day_n == 24 && mon_n == 12)) lights_ctrl.turn_off();  // Turn off at 23:00 if today is not 24.12
  if ((day_n == 25 && mon_n == 12) && (hours == 2 && minutes == 0)) lights_ctrl.turn_off(); // Turn off if 2:00 if today is 25.12 (night after 24.12)
}

void print_tim(){
  // debug
  Serial.begin(9600);
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.print(sec);
  Serial.print("_");
  Serial.println(day_n);
  Serial.end();
}
