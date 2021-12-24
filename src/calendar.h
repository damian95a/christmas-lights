#pragma once
#include "simplevector.h"

template <typename T>
struct date{
  T day;
  T month;
};

template <typename T>
using SV = SimpleVector<date<T>>;

template <typename T>
class Calendar : private SimpleVector<date<T>>{
  private:
  T year;
  T day_n(T d, T m, T y) const;

  public:
  Calendar() = default;
  Calendar(T y) : year{y}{}
  Calendar(T y, int siz) : year{y}, SimpleVector<date<T>>(siz){}

  void fill_cal();
  void print_cal() const;

  bool check_date(T _day, T _mon) const;
};
