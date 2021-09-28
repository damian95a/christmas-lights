#include "calendar.h"

// algorytm działa tylko dla stycznia i lutego!!!
// więc się nie ciesz na zapas
// tu trzebaby dodać 1 do roku, bo f. wykona się rok wczesniej niz bedzie potrzebna
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
  T day, tmp, jan7;
  jan7 = day_n(7,1, year+1); // it is a temporary var, that will be used to find first Saturday (or Sunday) after 06.01
  
  // check if 7th Jan is part of weekend
  if(jan7%6) tmp=6-jan7;
  else tmp=0;
  
  // if it isn't weekend, correct it
  day=7+tmp;
  int i;
  int n=SV<T>::s;
  for(i=0; i<n; i+=2, day+=7){
    
    // if Saturday is in January, save it
    if(day <= 31){
      (SV<T>::elem+i)->day=day;
      (SV<T>::elem+i)->month=1;
    }
    else if(day-31 == 1){ // if it isn't and is 1st Feb, save it
       (SV<T>::elem+i)->day=1;
       (SV<T>::elem+i)->month=2;
    }
    
    // if 7th Jan is Sun 
    if(jan7==0 && i==0){
      // it is used, to not save Monday as part of Weekend (nexst day - look bottom of function)
      --day;  // it is nessesery to get Saturday after +=7
      --i;
    }
    
    // save the next day (Sunday)
    if(day+1 <= 31){
      (SV<T>::elem+i+1)->day=day+1;
      (SV<T>::elem+i+1)->month=1;
    }
    else if(day == 31){ // if it's not January
      (SV<T>::elem+i+1)->day=1;
      (SV<T>::elem+i+1)->month=2;
    }
  }

  date<T> tmp_date;
  while(day<33){
    // if Saturday is in January, save it
    if(day <= 31) tmp_date = (date<T>){day, 1};
    else if(day-31 == 1) tmp_date = (date<T>){1, 2}; // if it isn't and is 1st Feb, save it

    SV<T>::push_back(tmp_date);
    
    // if 7th Jan is Sun 
    if(jan7==0 && i==0){
      // it is used, to not save Monday as part of Weekend (nexst day - look bottom of function)
      --day;  // it is nessesery to get Saturday after +=7
    }
    
    // save the next day (Sunday)
    if(day+1 <= 31) tmp_date = (date<T>){day+1, 1};
    else if(day == 31) tmp_date = (date<T>){1, 2}; // if it's not January

    SV<T>::push_back(tmp_date);
    day+=7;
  }
}

template <typename T>
void Calendar<T>::print_cal() const{
  Serial.begin(9600);

  for(int i=0; i < SV<T>::s; ++i){
      T d = (SV<T>::elem+i)->day;
      T m = (SV<T>::elem+i)->month;

      if(d<10) Serial.print("0");
      Serial.print(d);

      Serial.print(".");

      if(m<10) Serial.print("0");
      Serial.println(m);
  }

  Serial.end();
}
