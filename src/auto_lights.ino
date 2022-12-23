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

#define CHECK_INTERVAL 12000
#define CLOCK_INTERVAL (time_debug ? 1000 : CHECK_INTERVAL)

RTC_DS1307 RTC;

void readTime(); // save time to global variables
void lState(); // Turn on/off lights on time
void print_time();


short hours, minutes, sec, day_n, mon_n, year_n; // Time variables
long long last_check=-CHECK_INTERVAL, last_read=0;
bool time_debug=false;

// Controller pin 12
// Turn on by low but now turn it off (it's default state)
Lights lights_ctrl(12, LOW);
Schedule<short> cal; // save dates as short variables


////////////////////////////START////////////////////////////
void setup()
{
  Serial.begin(9600);
  
  // Turn off diode at pin no. 13 (to save energy)
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // Init RTC
  Wire.begin();
  RTC.begin();
  // following line sets the RTC to the date & time this sketch was compiled
  // RTC.adjust(DateTime(__DATE__, __TIME__)); // Uncomment to set the clock
  
  readTime();
  cal = Schedule<short>(year_n, mon_n); // initialize schedule

  // turn on in case of restart
  if ((CHRISTMAS(day_n, mon_n) || cal.check_date(day_n, mon_n)) && hours >= 16 && hours < 23) {
      lights_ctrl.turn_on();
    }
}

void loop()
{
  if(millis()-last_read >= CLOCK_INTERVAL){
    last_read = millis();
    // Get time now
    readTime();

    if(time_debug) print_time();
  }

  if(millis()-last_check >= CHECK_INTERVAL){
    last_check = millis();
    
    // Turn on every day in December
    // Turn on every day until 06.01 (Three Kings' Day)
    // Then only wheekends
    if (CHRISTMAS(day_n, mon_n) || cal.check_date(day_n, mon_n)) {
      lState();
    }
  }
}

void serialEvent(){
  String c = Serial.readStringUntil('\n');

  if(c == "start time debug"){
    time_debug=true;
  } else if(c == "stop time debug"){
    time_debug=false;
  } else if(c == "time"){
    readTime();
    print_time();
  } else if(c == "state"){
    Serial.println(lights_ctrl.get_state() ? "ON" : "OFF");
  } else if(c == "schedule"){
    cal.print();
  } else {
    Serial.println("Unknown command");
  }
}
////////////////////////////STOP////////////////////////////



void readTime(){
  // sign time to global variables
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
  if ((hours == 23 && minutes == 0) && !((day_n == 24 || day_n == 31) && mon_n == 12)) lights_ctrl.turn_off();  // Turn off at 23:00 if today is not 24.12/31.12
  if (((day_n == 25 && mon_n == 12) || (day_n == 1 && mon_n == 1)) && (hours == 2 && minutes == 0)) lights_ctrl.turn_off(); // Turn off if 2:00 and today is 25.12 of 01.01 (night after 24.12/31.12)
}

void print_time(){
  // debug
  Serial.print(hours);
  Serial.print(":");
  if(minutes<10) Serial.print(0);
  Serial.print(minutes);
  Serial.print(":");
  if(sec<10) Serial.print(0);
  Serial.print(sec);

  Serial.print(" ");
  Serial.print(day_n);
  Serial.print(".");
  Serial.print(mon_n);
  Serial.print(".");
  Serial.println(year_n);
}
