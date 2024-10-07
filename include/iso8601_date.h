#ifndef iso8601_date_h
#define iso8601_date_h

#include <stdexcept>
#include <ostream>

namespace ISO8601 {

  constexpr bool isleapyear (int year) {
    return (year % 4 == 0) & !((year % 100 == 0) & (year % 400 != 0));
  }


  class Date {
    public:

      enum DateType {YEAR, YEARMONTHDAY, YEARWEEKDAY, YEARDAY};


      Date(int year) : type_{YEAR}, year_{year} {
      }

      DateType type() const {
        return type_;
      }

      // YEAR
      int year() const {
        return year_;
      }

      // MONTH
      void set_month(int month) {
        if (month < 1 || month > 12 || (type_ != YEAR && type_ != YEARMONTHDAY)) 
          throw std::runtime_error("Invalid date.");
        if (type_ == YEAR) type_ = YEARMONTHDAY;
        month_ = month;
      }

      bool has_month() const {
        return month_ > 0;
      }

      int month() const {
        if (month_ < 1 || type_ != YEARMONTHDAY) 
          throw std::runtime_error("Date does not have a month.");
        return month_;
      }

      // DAY
      void set_day(int day) {
        if (day < 1 || day > 31 || type_ != YEARMONTHDAY || !has_month()) 
          throw std::runtime_error("Invalid date.");
        day_ = day;
      }

      bool has_day() const {
        return day_ > 0;
      }

      int day() const {
        if (day_ < 1 || type_ != YEARMONTHDAY) 
          throw std::runtime_error("Date does not have a day.");
        return day_;
      }

      // WEEK
      void set_week(int week) {
        if (week < 1 || week > 53 || (type_ != YEAR && type_ != YEARWEEKDAY)) 
          throw std::runtime_error("Invalid date.");
        if (type_ == YEAR) type_ = YEARWEEKDAY;
        week_ = week;
      }

      bool has_week() const {
        return week_ > 0;
      }

      int week() const {
        if (week_ < 1 || type_ != YEARWEEKDAY) 
          throw std::runtime_error("Date does not have a week.");
        return week_;
      }

      // WEEKDAY
      void set_weekday(int weekday) {
        if (weekday < 1 || weekday > 7 || type_ != YEARWEEKDAY || !has_week()) 
          throw std::runtime_error("Invalid date.");
        weekday_ = weekday;
      }

      bool has_weekday() const {
        return weekday_ > 0;
      }

      int weekday() const {
        if (weekday_ < 1 || type_ != YEARWEEKDAY) 
          throw std::runtime_error("Date does not have a week day.");
        return weekday_;
      }

      // YEARDAY
      void set_yearday(int yearday) {
        if (yearday < 1 || yearday > 366 || (type_ != YEAR && type_ != YEARDAY)) 
          throw std::runtime_error("Invalid date.");
        if (!isleapyear(year_) && yearday > 365)
          throw std::runtime_error("Invalid date.");
        if (type_ == YEAR) type_ = YEARDAY;
        yearday_ = yearday;
      }

      bool has_yearday() const {
        return yearday_ > 0;
      }

      int yearday() const {
        if (yearday_ < 1 || type_ != YEARDAY) 
          throw std::runtime_error("Date does not have a yearday.");
        return yearday_;
      }


    private:

      DateType type_;
      int year_;
      // YEARWEEKDAY
      int month_ = -1;
      int day_ = -1;
      // YEARWEEKDAY
      int week_ = -1;
      int weekday_ = -1;
      // YEARDAY
      int yearday_ = -1;
  };


  Date fillmissing(Date date);
  std::ostream& operator<<(std::ostream& stream, const Date& date);

  bool iscomplete(const Date& date);

  Date toyearmonthday(const Date& date);
  Date toyearday(const Date& date);
  Date toyearweekday(const Date& date);


}

#endif
