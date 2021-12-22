#include "calendar.h"

// !!!This algorithm is optimalized espetially for January and February!!!
// It doesn't work for other months
// We adds 1 to year number, because this fun will be called at the beginning of the winter (we need it after New Year)
template <typename T>
T Calendar<T>::day_n(T d, T m, T y) const {
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
void Calendar<T>::fill_cal(){
  // this function make a list of Sundays and Saturnadys between 07.01 and 01.02
  T day, tmp;
  tmp = day_n(6,1, year+1); // it is a temporary var, that will be used to find first Saturday (or Sunday) after 06.01
  
  tmp=6-tmp;
  if(!tmp) tmp=1;
   
  // set first day to check
  day=6+tmp;

  int i=0;
  // case if 7th Jan is saturday
  if(day_n(day,1,year+1) == 0){
    (this->elem[i]).day=day;
    (this->elem[i++]).month=1;
    day+=6;
    push_back((date<short>){0,0});
  }

  for(;i<size(); day+=7){
    
    // if Saturday is in January, save it
    if(day <= 31){
      (this->elem[i]).day=day;
      (this->elem[i++]).month=1;
    } else if(day == 32){ // if it isn't and is 1st Feb, save it
       (this->elem[i]).day=1;
       (this->elem[i++]).month=2;
    }


    // if Saturday is in January, save it
    if(day < 31){
      (this->elem[i]).day=day+1;
      (this->elem[i++]).month=1;
    } else if(day == 31){ // if it isn't and is 1st Feb, save it
       (this->elem[i]).day=1;
       (this->elem[i++]).month=2;
    }
  }

  while(true){
    
    // if Saturday is in January, save it
    if(day <= 31){
      date<short> move_date = {day,1};
      push_back(move_date);
    } else if(day == 32){ // if it isn't and is 1st Feb, save it
      date<short> move_date = {1,2};
      push_back(move_date);
      break;
    } else {break;}

    // if Saturday is in January, save it
    if(day < 31){
      date<short> move_date = {day+1,1};
      push_back(move_date);
    } else if(day == 31){ // if it isn't and is 1st Feb, save it
      date<short> move_date = {1,2};
      push_back(move_date);
      break;
    } else {break;}

    day+=7;
  }

  // add 02.02 at the end
  push_back((date<T>){2,2});
}

template <typename T>
void Calendar<T>::print_cal() const{
  Serial.begin(9600);

  for(int i=0; i < this->s; ++i){
      T d = (this->elem[i]).day;
      T m = (this->elem[i]).month;

      if(d<10) Serial.print("0");
      Serial.print(d);

      Serial.print(".");

      if(m<10) Serial.print("0");
      Serial.println(m);
  }

  Serial.end();
}

template <typename T>
bool Calendar<T>::check_date(T _day, T _mon) const {
  for(auto p=begin(); p<end(); ++p){
    if(p->day == _day && p->month == _mon){
      return true; // true if any from list matches
    }
  }

  return false; // false if none from list matches
}
