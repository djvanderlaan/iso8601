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

}
