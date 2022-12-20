#ifndef SCHEDULE_H
#define SCHEDULE_H

#define BASIC_SIZE 9
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

/**
 * this class stores the days when to turn lights on
 * in this case we assign here weekends in January an February
 */
template <typename T>
class Schedule{
  public:
  /**
   * default constructor
   */
  Schedule() : size{0} {}

  /**
   * This constructor generates schedule depending on year
   * @param y current year at the time when it is called
   * @param m current month at the time when it is called
   */
  Schedule(T y, T m);

  /**
   * It prints the list of dates e.g. for debug
   */
  void print() const;

  /**
   * it checks the condition
   * if given date is in the list
   * @param _day day of date to be checked
   * @param _mon month of date to be checked
   * @return true if given day is in the schedule
   */
  bool check_date(T _day, T _mon) const;

  private:
  date<T> sch[BASIC_SIZE];
  uint8_t size;

  /**
   * this is algorithm that calculates day of week
   * @param d day of month
   * @param m month
   * @param y year that calculated day is in
   * @return day of week code e.g. Sunday - 0, Monday - 1, ..., Saturday - 6
   */
  T day_n(T d, T m, T y) const;
  
  /**
   * fills an array of dates with weekends between 07.01 and 01.02
   * depends on year (every year the weekends are the other days)
   * @param year this is year in which the weekends will be searched for
   */
  void fill_sch(T year);
};

#endif
