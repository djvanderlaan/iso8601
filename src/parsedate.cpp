
#include "iso8601.h"
#include "utils.h"

namespace ISO8601 {

  int getint(const std::string_view str, std::string_view::size_type nchar) {
    return strtoint(str.substr(0, nchar));
  }


  Date parsedate(std::string_view str) {
    //std::string_view::size_type pos = 0;
    if (str.size() < 1) throw std::runtime_error("Invalid ISO8601 date");
    int sign = 1;
    if (str.front() == '+' || str.front() == '-') {
      if (str.front() == '-') sign = -1L;
      str.remove_prefix(1);
    }
    // Year
    const auto nnum = count_numeric(str);
    if (nnum < 4) {
      // TODO:we have parial year; for now we don't accept this
      throw std::runtime_error("Invalid ISO8601 date");
    }
    Date result{sign * getint(str, 4L)};
    str.remove_prefix(4);
    // Determine if we have extended format e.g. YYYY-MM-DD or compact 
    // format e.g. YYYYMMDD; if we have extended format - needs to be used all
    // the time and vice versa
    const bool extended_format = starts_with(str, '-');
    if (extended_format) str.remove_prefix(1);
    // Month or week or yearday
    if (starts_with(str, 'W')) {
      // week
      str.remove_prefix(1);
      if (str.size() < 2) throw std::runtime_error("Invalid ISO8601 date");
      result.set_week(getint(str, 2));
      str.remove_prefix(2);
    } else if (str.size() == 3) {
      // yearday
      result.set_yearday(getint(str, 3));
      str.remove_prefix(3);
    } else if (str.size() >= 2) {
      // month
      result.set_month(getint(str, 2));
      str.remove_prefix(2);
    }
    // Next item; if extended format we expect - and vice versa
    if (str.size() > 0) {
      if ((str[0] == '-') != extended_format)
        throw std::runtime_error("Invalid ISO8601 date");
      if (str[0] == '-') str.remove_prefix(1);
      // we can't have '-' at the end
      if (str.size() == 0) 
        throw std::runtime_error("Invalid ISO8601 date");
    }
    // Weekday
    if (str.size() > 0 && result.type() == Date::YEARWEEKDAY) {
      result.set_weekday(getint(str, 1));
      str.remove_prefix(1);
    }
    // Day of month
    if (str.size() > 0 && result.type() == Date::YEARMONTHDAY) {
      if (str.size() < 2) throw std::runtime_error("Invalid ISO8601 date");
      result.set_day(getint(str, 2));
      str.remove_prefix(2);
    }
    // Date YYYYMM is not allowed to avoid confusion with YYMMDD
    if (!extended_format && result.type() == Date::YEARMONTHDAY && !result.has_day()) 
      throw std::runtime_error("Invalid ISO8601 date");
    if (str.size() > 0) throw std::runtime_error("Invalid ISO8601 date");
    return result;
  }

}
