#include "parsetime.h"
#include "utils.h"

#include <iostream>
#include <utility>


bool isnumchar(char c) {
  return (c >= '0' && c <= '9');
}
bool isdecimal(char c) {
  return c == '.' || c == ',';
}

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
  const std::string vstr{str.substr(0, pos)};
  double val = std::stod(vstr, nullptr);
  return std::make_pair(val, isfraction);
}

bool timezonestart(char c) {
  return c == 'Z' || c == '+' || c == '-';
}

ISOTimezone parse_timezone(const std::string_view& str, std::string_view::size_type& pos) {
  const auto end = str.size();
  pos = 0;
  const auto nchar_remain = end - pos;
  if (nchar_remain == 0) {
    return ISOTimezone{};
  } else if (nchar_remain == 1 && str.at(pos) == 'Z') {
    return ISOTimezone{false};
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
    return ISOTimezone{false, hour, minutes};
  } else {
    throw std::runtime_error("Invalid time zone");
  }
}

ISOTime parsetime(std::string_view str) {
  std::string_view::size_type pos = 0;
  if (str.size() < 1) throw std::runtime_error("Invalid ISO8601 time");
  if (str.front() == 'T') str.remove_prefix(1);

  // Hours
  auto [hour, hour_fractional] = readfractime(str, pos);
  str = str.substr(pos);
  // Minutes
  bool extended_format = false;
  bool has_minutes = false;
  double minutes = 0.0;
  bool minutes_fractional = true;
  if (!hour_fractional && str.size() > 0 && !timezonestart(str[0])) {
    // Check if we have HH:MM or HHMM
    if (str[0] == ':')  {
      extended_format = true;
      str.remove_prefix(1);
    }
    const auto r = readfractime(str, pos);
    minutes = r.first;
    minutes_fractional = r.second;
    has_minutes = true;
    str = str.substr(pos);
  }
  // Seconds
  bool has_seconds = false;
  double seconds = 0.0;
  bool seconds_fractional = true;
  if (has_minutes && !minutes_fractional && str.size() > 0 && 
      !timezonestart(str[0])) {
    // Check if we have HH:MM or HHMM
    const bool colon = str[0] == ':';
    if (colon != extended_format)
      throw std::runtime_error("Invalid ISO8601 time");
    if (str[0] == ':')  str.remove_prefix(1);
    const auto r = readfractime(str, pos);
    seconds = r.first;
    seconds_fractional = r.second;
    has_seconds = true;
    str = str.substr(pos);
  }
  // Timezone
  auto tz = parse_timezone(str, pos);
  // Output result
  std::cout << "HOUR = " << hour << "\n";
  if (has_minutes) std::cout << "MINUTES = " << minutes << "\n";
  if (has_seconds) std::cout << "SECONDS = " << seconds << "\n";
  std::cout << "TIMEZONE = " << tz << "\n";
  return ISOTime{};
}

