
#include <stdexcept>
#include "iso8601_datetime.h"

namespace ISO8601 {

  std::ostream& operator<<(std::ostream& stream, const Datetime& datetime) {
    stream << datetime.date() << datetime.time();
    return stream;
  }

  Date subtractday(Date date) {
    if (date.type() == Date::YEARWEEKDAY) {
      throw std::runtime_error("tozulu() not defined for dates of type YEARWEEKDAY.");
    } else if (date.type() == Date::YEARMONTHDAY) {
      if (!date.has_day() || !date.has_month()) 
        throw std::runtime_error("Incomplete date.");
      int day = date.day() - 1L;
      int month = date.month();
      int year = date.year();
      if (day < 1L) {
        switch (month) {
          case 1:
            day = 31L;
            month = 12L;
            year -= 1L;
            break;
          case 3:
            day = isleapyear(year) ? 29L : 28L;
            month = 2L;
            break;
          case 2:
          case 4:
          case 6:
          case 8:
          case 9:
          case 11:
            day = 31L;
            month -= 1L;
            break;
          case 5:
          case 7:
          case 10:
          case 12:
            day = 30L;
            month -= 1L;
            break;
        }
      }
      date = Date{year};
      date.set_month(month);
      date.set_day(day);
    } else if (date.type() == Date::YEARDAY) {
      if (!date.has_yearday()) 
        throw std::runtime_error("Incomplete date.");
      if (date.yearday() == 1L) {
        date = Date{date.year() - 1};
        if (isleapyear(date.year())) {
          date.set_yearday(366L);
        } else {
          date.set_yearday(365L);
        }
      } else {
        date.set_yearday(date.yearday() - 1L);
      }
    }
    return date;
  }

  int ndaysinmonth(int year, int month) {
    switch (month) {
      case 4:
      case 6:
      case 9:
      case 11:
        return 30;
      case 2:
        return isleapyear(year) ? 29 : 28;
      default:
        return 31;
    }
  }

  Date addday(Date date) {
    if (date.type() == Date::YEARWEEKDAY) {
      throw std::runtime_error("tozulu() not defined for dates of type YEARWEEKDAY.");
    } else if (date.type() == Date::YEARMONTHDAY) {
      if (!date.has_day() || !date.has_month()) 
        throw std::runtime_error("Incomplete date.");
      int day = date.day() + 1L;
      int month = date.month();
      int year = date.year();
      if (day > ndaysinmonth(year, month)) {
        day = 1L;
        month += 1L;
        if (month > 12L) {
          month = 1L;
          year += 1L;
        }
      }
      date = Date{year};
      date.set_month(month);
      date.set_day(day);
    } else if (date.type() == Date::YEARDAY) {
      if (!date.has_yearday()) 
        throw std::runtime_error("Incomplete date.");
      int ndaysinyear = isleapyear(date.year()) ? 366 : 365;
      if (date.yearday() == ndaysinyear) {
        date = Date{date.year() + 1};
        date.set_yearday(1L);
      } else {
        date.set_yearday(date.yearday() + 1L);
      }
    }
    return date;
  }

  Datetime tozulu(const Datetime& datetime) {
    Date d = datetime.date();
    Time t = datetime.time();
    Timezone tz = t.timezone();
    if (tz.localtime() || (tz.offset_hours() == 0 && tz.offset_minutes() == 0)) 
      return datetime;
    if (tz.offset_minutes() != 0 && !t.has_minutes())
      throw std::runtime_error("Incomplete time.");
    // update minutes
    double minutes = tz.offset_hours() < 0 ? t.minutes() + tz.offset_minutes() : 
      t.minutes() - tz.offset_minutes();
    double hour    = t.hour() - tz.offset_hours();
    if (minutes < 0) {
      hour -= 1;
      minutes += 60;
    } else if (minutes >= 60) {
      hour += 1;
      minutes -= 60;
    }
    // update hour
    if (hour < 0) {
      hour += 24;
      d = subtractday(d);
    } else if (hour >= 24) {
      hour -= 24;
      d = addday(d);
    }
    t.set_hour(hour, t.hour_fractional());
    t.set_minutes(minutes, t.minutes_fractional());
    t.set_timezone(Timezone{false, 0, 0});
    return Datetime(d, t);
  }

  Datetime fillmissing(const Datetime& datetime) {
    return Datetime{fillmissing(datetime.date()), fillmissing(datetime.time())};
  }


}
