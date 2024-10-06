#include "iso8601_date.h"
#include <iomanip>
#include <array>
#include <cstdint>

#include <iostream>

namespace ISO8601 {

  Date fillmissing(Date date) {
    switch (date.type()) {
      case Date::YEAR:
        date.set_month(1);
        date.set_day(1);
        break;
      case Date::YEARMONTHDAY:
        if (!date.has_month()) date.set_month(1);
        if (!date.has_day()) date.set_day(1);
        break;
      case Date::YEARWEEKDAY:
        if (!date.has_weekday()) date.set_weekday(1);
      case Date::YEARDAY:
        // nothing to do
        break;
    }
    return date;
  }

  std::ostream& operator<<(std::ostream& stream, const Date& date) {
    stream << std::setw(4) << std::setfill('0') << date.year();
    if (date.type() == Date::YEARMONTHDAY) {
      if (date.has_month()) 
        stream << '-' << std::setw(2) << std::setfill('0') << date.month();
      if (date.has_day()) 
        stream << '-' << std::setw(2) << std::setfill('0') << date.day();
    } else if (date.type() == Date::YEARWEEKDAY) {
      if (date.has_week()) 
        stream << '-' << 'W' << std::setw(2) << std::setfill('0') << date.week();
      if (date.has_weekday()) 
        stream << '-' << std::setw(1) << date.weekday();
    } else if (date.type() == Date::YEARDAY) {
      if (date.has_yearday()) 
        stream << '-' << std::setw(3) << std::setfill('0') << date.yearday();
    }
    return stream;
  }


  Date toyearmonthday(const Date& date) {
    switch(date.type()) {
      case Date::YEAR:
        throw std::runtime_error("Incomplete date. Cannot convert to year-month-day.");
      case Date::YEARMONTHDAY:
        // do nothing already correct type
        return date;
      case Date::YEARDAY: 
      {
        const std::array<int, 26> monthstartday = {
          1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366,  // regular
          1, 32, 61, 92, 122, 153, 183, 214, 245, 275, 306, 336, 367   // leapyear
        };
        Date d{date.year()};
        int yearday = date.yearday();
        size_t offset = isleapyear(date.year()) ? 13 : 0;
        int month = 0;
        for (size_t i = 0; i < 13; ++i) 
          if (yearday >= monthstartday[i+offset]) month = i+1;
        d.set_month(month);
        d.set_day(yearday - monthstartday[month+offset-1L] + 1);
        return d;
      }
      case Date::YEARWEEKDAY:
        throw std::runtime_error("Cannot convert year-week-day to year-month-day. Not implemented.");
    }
    return date;
  }


  // The following contains the following information for the years 0..400. The 
  // Gregorian calendar has a 400 year period. 
  // - last 3 bits: the day of the week (0=mon, .. 7=sun) the 1st of January 
  //   falls on
  // - 4th bit: 1 if the year has 53 weeks and 0 if the year has 52 weeks
  //
  static const std::array<uint_fast8_t, 400> YEARSTARTDAY = {5, 0, 1, 2, 11, 5, 6, 0, 1, 
    11, 4, 5, 6, 1, 2, 11, 4, 6, 0, 1, 10, 4, 5, 6, 0, 2, 11, 4, 5, 0, 1, 2, 
    11, 5, 6, 0, 1, 11, 4, 5, 6, 1, 2, 11, 4, 6, 0, 1, 10, 4, 5, 6, 0, 2, 11, 
    4, 5, 0, 1, 2, 11, 5, 6, 0, 1, 11, 4, 5, 6, 1, 2, 11, 4, 6, 0, 1, 10, 4, 
    5, 6, 0, 2, 11, 4, 5, 0, 1, 2, 11, 5, 6, 0, 1, 11, 4, 5, 6, 1, 2, 11, 4, 
    5, 6, 0, 1, 11, 4, 5, 6, 1, 2, 11, 4, 6, 0, 1, 10, 4, 5, 6, 0, 2, 11, 4, 
    5, 0, 1, 2, 11, 5, 6, 0, 1, 11, 4, 5, 6, 1, 2, 11, 4, 6, 0, 1, 10, 4, 5, 
    6, 0, 2, 11, 4, 5, 0, 1, 2, 11, 5, 6, 0, 1, 11, 4, 5, 6, 1, 2, 11, 4, 6, 
    0, 1, 10, 4, 5, 6, 0, 2, 11, 4, 5, 0, 1, 2, 11, 5, 6, 0, 1, 11, 4, 5, 6, 
    1, 2, 11, 4, 6, 0, 1, 2, 11, 4, 5, 6, 1, 2, 11, 4, 6, 0, 1, 10, 4, 5, 6, 
    0, 2, 11, 4, 5, 0, 1, 2, 11, 5, 6, 0, 1, 11, 4, 5, 6, 1, 2, 11, 4, 6, 0, 
    1, 10, 4, 5, 6, 0, 2, 11, 4, 5, 0, 1, 2, 11, 5, 6, 0, 1, 11, 4, 5, 6, 1, 
    2, 11, 4, 6, 0, 1, 10, 4, 5, 6, 0, 2, 11, 4, 5, 0, 1, 2, 11, 5, 6, 0, 1, 
    11, 4, 5, 6, 1, 2, 11, 4, 6, 0, 1, 10, 4, 5, 6, 0, 1, 2, 11, 4, 6, 0, 1, 
    10, 4, 5, 6, 0, 2, 11, 4, 5, 0, 1, 2, 11, 5, 6, 0, 1, 11, 4, 5, 6, 1, 2, 
    11, 4, 6, 0, 1, 10, 4, 5, 6, 0, 2, 11, 4, 5, 0, 1, 2, 11, 5, 6, 0, 1, 11, 
    4, 5, 6, 1, 2, 11, 4, 6, 0, 1, 10, 4, 5, 6, 0, 2, 11, 4, 5, 0, 1, 2, 11, 
    5, 6, 0, 1, 11, 4, 5, 6, 1, 2, 11, 4, 6, 0, 1, 10, 4, 5, 6, 0, 2, 11, 4};

  constexpr int dow1st(int year) {
    return (YEARSTARTDAY[year % 400] & 7)+1;
  }
  constexpr int nweeks(int year) {
    return (YEARSTARTDAY[year % 400] & 8) > 0 ? 53 : 52;
  }

}

/*
 *

isleapyear <- function(y) {
  (y %% 4 == 0) && !((y %% 100 == 0) && (y %% 400 != 0))
}

monthdays <- list(
  c(1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366), 
  c(1, 32, 61, 92, 122, 153, 183, 214, 245, 275, 306, 336, 367))
monthdays

year <- 2024
yearday <- 62
index <- ifelse(isleapyear(year), 2, 1)
mon <- which(yearday >= monthdays[[index]]) |> tail(1)
mon
yearday - monthdays[[index]][mon] + 1



day <- k

*/

