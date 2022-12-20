/*  Program to control christmas lights
 *  Relay 230V - turning on by LOW
 *  RTC I2C
 *  Arduino 5V
 */

#include "lights.h"
#include "schedule.h"
#include <Wire.h>
#include "RTClib.h" // Real time clock

// turn lights on every day 24.12-06.01
#define CHRISTMAS(d, m) (((m)==12 && (d)>=24) || ((m)==1 && (d)<=6))

RTC_DS1307 RTC;

void readTime(); // save time to global variables
void lState(); // Turn on/off lights on time
void print_tim(); // debug


short hours, minutes, day_n, mon_n, year_n; // Time variables

// Controller pin 12
// Turn on by low but now turn it off (it's default state)
Lights lights_ctrl = Lights(12, LOW);
Schedule<short> cal; // save dates as short variables

void setup()
{
  // Turn off diode at pin no. 13 (to save energy)
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // Init RTC
  Wire.begin();
  RTC.begin();
  // following line sets the RTC to the date & time this sketch was compiled
  // RTC.adjust(DateTime(__DATE__, __TIME__)); // Uncomment to set the clock
  
  readTime();

  
  cal = Schedule<short>(year_n, mon_n); // initialize callendar
  cal.print(); // print the weekends for debug

  // debug
  print_tim();
}

void loop()
{
  // Get time now
  readTime();

  // Turn on every day in December
  // Turn on every day until 06.01 (Three Kings' Day)
  // Then only wheekends
  if (CHRISTMAS(day_n, mon_n) || cal.check_date(day_n, mon_n)) {
    lState();
  }

  // it is to not chceck all the time
  // we need minutes, not seconds
  delay(12000); // change if doesn't work
}





void readTime(){
  // sign time to global variables
  DateTime now = RTC.now();// Getting the current Time and storing it into a DateTime object

  hours = now.hour();
  minutes = now.minute();

  day_n = now.day();
  mon_n = now.month();
  year_n = now.year();
}

void lState(){
  // Turn on/off lights on time
  if (hours == 16 && minutes == 0) lights_ctrl.turn_on(); // Turn on at 16:00
  if ((hours == 23 && minutes == 0) && !((day_n == 24 || day_n == 31) && mon_n == 12)) lights_ctrl.turn_off();  // Turn off at 23:00 if today is not 24.12/31.12
  if (((day_n == 25 && mon_n == 12) || (day_n == 1 && mon_n == 1)) && (hours == 2 && minutes == 0)) lights_ctrl.turn_off(); // Turn off if 2:00 and today is 25.12 of 01.01 (night after 24.12/31.12)
}

void print_tim(){
  // debug
  Serial.begin(9600);
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);

  Serial.print(" ");
  Serial.print(day_n);
  Serial.print(".");
  Serial.print(mon_n);
  Serial.print(".");
  Serial.println(year_n);
  Serial.end();
}
