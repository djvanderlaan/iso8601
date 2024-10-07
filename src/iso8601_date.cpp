#include "iso8601_date.h"
#include <iomanip>
#include <array>
#include <cstdint>

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
        break;
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

  bool iscomplete(const Date& date) {
    // Check if we have a full date
    switch (date.type()) {
      case Date::YEAR:
        return true;
      case Date::YEARMONTHDAY:
        if (!date.has_month() || !date.has_day())
          return false;
        break;
      case Date::YEARWEEKDAY:
        if (!date.has_week() || !date.has_weekday())
          return false;
        break;
      case Date::YEARDAY:
        if (!date.has_yearday())
          return false;
        break;
    }
    return true;
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

  // Week day of 1st of January: 1 = mon, ... , 7 = sun
  constexpr int dow1st(int year) {
    return (YEARSTARTDAY[year % 400] & 7)+1;
  }
  // Number of weeks in a given year
  constexpr int nweeks(int year) {
    return (YEARSTARTDAY[year % 400] & 8) > 0 ? 53 : 52;
  }
  // The number of days the first day of the first week is away from the 
  // first day of the year
  constexpr int weekoffset(int year) {
    int d = dow1st(year);
    switch (d) {
      case 1:
        return 0;
      case 2:
        return -1; // if 1st Jan is a Tuesday, the first day of the week 
                   // starts on 31st of December
      case 3:
        return -2;
      case 4:
        return -3;
      case 5:
        return 3;  // if 1st Jan is a Friday, the week start monday the 
                   // 4th of January
      case 6:
        return 2;
      case 7:
        return 1;
      default:
        throw std::runtime_error("Invalid weekday.");
    }
  }

  // Starting day of month counted from the 1st of January
  static const std::array<int, 26> MONTHSTARTDAY = {
    1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366,  // regular
    1, 32, 61, 92, 122, 153, 183, 214, 245, 275, 306, 336, 367   // leapyear
  };

  Date toyearday(const Date& date) {
    switch(date.type()) {
      case Date::YEAR:
        throw std::runtime_error("Incomplete date. Cannot convert to year-day.");
      case Date::YEARMONTHDAY:
      {
        Date d{date.year()};
        const size_t offset = isleapyear(date.year()) ? 13 : 0;
        d.set_yearday(MONTHSTARTDAY[date.month()+offset-1L] + date.day() - 1L);
        return d;
      }
      case Date::YEARDAY: 
        // do nothing already correct type
        return date;
      case Date::YEARWEEKDAY:
      {
        int year = date.year();
        int yearday = (date.week() - 1)*7 + date.weekday() + weekoffset(date.year());
        if (yearday < 1) year -= 1;
        Date d{year};
        const size_t offset = isleapyear(date.year()) ? 13 : 0;
        if (yearday < 1) yearday = MONTHSTARTDAY[offset+12] + yearday;
        d.set_yearday(yearday);
        return d;
      }
    }
    return date;
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
        Date d{date.year()};
        int yearday = date.yearday();
        size_t offset = isleapyear(date.year()) ? 13 : 0;
        int month = 0;
        for (size_t i = 0; i < 13; ++i) 
          if (yearday >= MONTHSTARTDAY[i+offset]) month = i+1;
        d.set_month(month);
        d.set_day(yearday - MONTHSTARTDAY[month+offset-1L] + 1);
        return d;
      }
      case Date::YEARWEEKDAY:
        const int yearday = (date.week() - 1)*7 + date.weekday() + weekoffset(date.year());
        if (yearday < 1) {
          // easier to go to month directly instead of working with negative yearday
          Date d{date.year()-1};
          d.set_month(12);
          d.set_day(31 + yearday);
          return d;
        } else {
          Date d{date.year()};
          size_t offset = isleapyear(date.year()) ? 13 : 0;
          int month = 0;
          for (size_t i = 0; i < 13; ++i) 
            if (yearday >= MONTHSTARTDAY[i+offset]) month = i+1;
          d.set_month(month);
          d.set_day(yearday - MONTHSTARTDAY[month+offset-1L] + 1);
          return d;
        }
    }
    return date;
  }

  Date toyearweekday(const Date& date) {
    switch(date.type()) {
      case Date::YEAR:
        throw std::runtime_error("Incomplete date. Cannot convert to year-month-day.");
      case Date::YEARMONTHDAY:
        return toyearweekday(toyearday(date));
      case Date::YEARDAY: 
      {
        const int offset = weekoffset(date.year());
        int week = (-offset + date.yearday()-1 + 7) / 7;
        int year = date.year();
        // calculate weekday before we change year or week around year border
        const int weekday = (dow1st(year) + date.yearday() - 2) % 7 +1;
        if (week < 1) {
          year = year - 1;
          week = nweeks(year) + week;
        } else if (week > nweeks(year)) {
          week = 1;
          year = year + 1;
        }
        Date d{year};
        d.set_week(week);
        d.set_weekday(weekday);
        return d;
      }
      case Date::YEARWEEKDAY:
        // do nothing already correct type
        return date;
    }
    return date;
  }

}

