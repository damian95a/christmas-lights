#include "schedule.h"

template <typename T>
Schedule<T>::Schedule(T year, T month) : size{0} {
  // calculation of yeay reminder (if program is ran before NY)
  uint8_t calc_year_rem = (month > 6) ? 1 : 0; // it is necessary to add 1 to year, because it generates schedule for Januay
  fill_sch(year+calc_year_rem); // fill an array
}

// !!!This algorithm is optimalized espetially for January and February!!!
// It doesn't work for other months
template <typename T>
T Schedule<T>::day_n(T d, T m, T y) const {
  // it is an algorithm to find day of week, that is optimalized for January and February
  /* Sun - 0
   * ...
   * Sat - 6
   */
  T name, tmp;
  
  tmp = 23*m;
  name = tmp/9 + d + y + 4;
  
  --y;
  tmp = y/4;
  name += tmp;
  
  tmp = y/100;
  name -= tmp;
  
  tmp = y/400;
  name += tmp;
  
  return name%7;
}

template <typename T>
void Schedule<T>::fill_sch(T year){
  // this constructor make an array of Sundays and Saturnadys between 07.01 and 01.02 and additionaly 02.02
  T day, tmp;
  
  tmp = day_n(6,1, year); // it is a temporary var, that will be used to find first Saturday (or Sunday) after 06.01
  
  tmp=6-tmp;
  if(!tmp) tmp=1;
   
  // set first day to be checked
  day=6+tmp;

  int i=0;
  for(; i<BASIC_SIZE; ++i){
    if(day == 32){
      sch[i] = {1, 2};
      break;
    }
    else if(day < 32){
      sch[i] = {day, 1};
  
      if(day_n(day, 1, year) == 6) day += 1;
      else day += 6;
    }
    else {
      i-=1;
      break;
    }
  }

  size = i+2;

  // add 02.02 at the end
  sch[size-1] = {2,2};
}

template <typename T>
void Schedule<T>::print() const{
  Serial.println("Schedule:");
  for(int i=0; i < size; ++i){
      T d = sch[i].day;
      T m = sch[i].month;

      if(d<10) Serial.print("0");
      Serial.print(d);

      Serial.print(".");

      if(m<10) Serial.print("0");
      Serial.println(m);
      
  }

  Serial.print("Size: ");
  Serial.println(size);
}

template <typename T>
bool Schedule<T>::check_date(T _day, T _mon) const {
  for(auto p=sch; p != sch+size; ++p){
    if(p->day == _day && p->month == _mon){
      return true; // true if any from list matches
    }
  }

  return false; // false if none from list matches
}
