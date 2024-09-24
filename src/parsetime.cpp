#include "iso8601.h"
#include "utils.h"

namespace ISO8601 {

typedef std::pair<double, bool> Fractional;

  Fractional readfractime(const std::string_view& str, std::string_view::size_type& pos) {
    pos = 0;
    // We expect two digits
    if (str.size() < 2 || !isnumchar(str[0]) || !isnumchar(str[1]))
      throw std::runtime_error("Invalid ISO8601 time");
    pos += 2;
    // Possibly followed by a decimal sign
    const bool isfraction = str.size() > 2 && isdecimal(str[2]);
    if (isfraction) {
      // now we expect more numbers
      if (str.size() < 4 || !isnumchar(str[3])) 
        throw std::runtime_error("Invalid ISO8601 time");
      pos += 2;
      for ( ; pos < str.size(); ++pos) {
        if (!isnumchar(str[pos])) break;
      }
    }
    // convert result to double
    std::string vstr{str.substr(0, pos)};
    for (auto& c: vstr) if (isdecimal(c) && c != '.') c = '.';
    double val = std::stod(vstr, nullptr);
    return std::make_pair(val, isfraction);
  }

  bool timezonestart(char c) {
    return c == 'Z' || c == '+' || c == '-';
  }

  Timezone parse_timezone(const std::string_view& str, std::string_view::size_type& pos) {
    const auto end = str.size();
    pos = 0;
    const auto nchar_remain = end - pos;
    if (nchar_remain == 0) {
      return Timezone{};
    } else if (nchar_remain == 1 && str.at(pos) == 'Z') {
      return Timezone{false};
    } else if (str.at(pos) == '-' || str.at(pos) == '+') {
      if (nchar_remain < 3) throw std::runtime_error("Invalid time zone");
      int hour = strtoint(str.substr(pos, pos+3));
      pos += 3;
      int minutes = 0;
      if (nchar_remain == 3) {
        // do nothing; hours is already parsed
      } else if (nchar_remain == 5) {
        minutes = strtoint(str.substr(pos,pos+2));
        pos += 2;
      } else if (nchar_remain == 6) {
        minutes = strtoint(str.substr(pos+1,pos+3));
        pos += 3;
      } else {
        throw std::runtime_error("Invalid time zone");
      }
      return Timezone{false, hour, minutes};
    } else {
      throw std::runtime_error("Invalid time zone");
    }
  }

  Time parsetime(std::string_view str) {
    std::string_view::size_type pos = 0;
    if (str.size() < 1) throw std::runtime_error("Invalid ISO8601 time");
    const bool starts_with_T = str.front() == 'T';
    if (starts_with_T) str.remove_prefix(1);

    // Hours
    const auto r = readfractime(str, pos);
    Time result{r.first, r.second};
    str = str.substr(pos);
    // Minutes
    bool extended_format = false;
    if (!result.hour_fractional() && str.size() > 0 && !timezonestart(str[0])) {
      // Check if we have HH:MM or HHMM
      if (str[0] == ':')  {
        extended_format = true;
        str.remove_prefix(1);
      }
      const auto r = readfractime(str, pos);
      str = str.substr(pos);
      result.set_minutes(r.first, r.second);
    }
    // A check; we don't accept compact format without T
    if (!extended_format && !starts_with_T)
      throw std::runtime_error("Invalid ISO8601 time");
    // Seconds
    if (result.has_minutes() && !result.minutes_fractional() && str.size() > 0 && 
        !timezonestart(str[0])) {
      // Check if we have HH:MM or HHMM
      const bool colon = str[0] == ':';
      if (colon != extended_format)
        throw std::runtime_error("Invalid ISO8601 time");
      if (str[0] == ':')  str.remove_prefix(1);
      const auto r = readfractime(str, pos);
      str = str.substr(pos);
      result.set_seconds(r.first, r.second);
    }
    // Timezone
    auto tz = parse_timezone(str, pos);
    result.set_timezone(tz);
    // Output result
    return result;
  }

}
