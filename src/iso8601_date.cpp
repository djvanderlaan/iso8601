#include "iso8601_date.h"
#include <iomanip>


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
    if (data.type() == Date::YEARDAY) {
      Date d{date.year()};
      int yearday = date.yearday();

      return d;
    }
    return date;
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

