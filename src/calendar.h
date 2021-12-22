#pragma once
#include "simplevector.h"

/**
 * it holds short date (day and month)
 * it is template to fit type
 * e.g. if you want to save memory
 */
template <typename T>
struct date{
  T day;
  T month;
};

template <typename T>
using SV = SimpleVector<date<T>>;

/**
 * this class stores the days when to turn lights on
 * in this case we assign here weekends in January an February
 */
template <typename T>
class Calendar : private SimpleVector<date<T>>{
  private:
  T year;

  /**
   * this is algorithm that returns name of the day
   * e.g. Sunday (returns 0), Monday (returns 1), ..., Saturday (returns 6)
   */
  T day_n(T d, T m, T y) const;

  public:
  /**
   * default constructor
   */
  Calendar() = default;

  /**
   * This constructor gets year
   * Vector is default
   */
  Calendar(T y) : year{y}{}

  /**
   * This constructor gets year and size
   * It generates empty vector of this size
   */
  Calendar(T y, int siz) : year{y}, SimpleVector<date<T>>(siz){}

  /**
   * This algorithm generates list of weekends in ranage 07.01-01.02
   * it also adds 02.02 at the end
   */
  void fill_cal();

  /**
   * It prints the list e.g. for debug
   */
  void print_cal() const;

  /**
   * it checks the condition
   * if given date is in the list
   */
  bool check_date(T _day, T _mon) const;
};
