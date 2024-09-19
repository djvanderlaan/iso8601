#include "parsetime.h"
#include <iostream>
#include <utility>


bool isnumchar(char c) {
  return (c >= '0' && c <= '9');
}
bool isdecimal(char c) {
  return c == '.' || c == ',';
}

typedef std::pair<double, bool> Fractional;

Fractional readfractime(std::string_view str, std::string_view::size_type& pos) {
  // We expect two digits
  if (str.size() < 2 || !isnumchar(str[0]) || !isnumchar(str[1]))
    throw std::runtime_error("Invalid ISO8601 time");
  pos += 2;
  // Possibly followed by a decimal sign
  const bool isfraction = str.size() > 2 && isdecimal(str[2]);
  if (isfraction) {
    // now we expect more numbers
    if (str.size() < 4 || !isnumchar(str.at(3))) 
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



double parsehour(std::string_view str, std::string_view::size_type& pos) {
  /*if (str.size() < 2) throw std::runtime_error("Invalid ISO8601 time");
  std::string_view hour = str.substr(0, 2);
  if (!all_num(hour)) throw std::runtime_error("Invalid ISO8601 time");
  std::cout << "HOUR = '" << hour << "'\n";
  str.remove_prefix(2);
  // check for fractional hour
  if (str.size() > 0 && str.front() == '.') {
    str.remove_prefix(1);
    parse_fraction(str);
  // check if we have the start of a time zone
  } else if (str.size() > 0 && timezonestart(str.front())) {
    parse_timezone(str);
  // if we have characters left this should be minutes
  } else if (str.size() > 0) {
    parse_minutes(str);
  } else {
    parse_timezone(str);
  }*/
  auto [res, fraction] = readfractime(str, pos);
  std::cout << "HOUR = " << res << "\n";
  return res;
}

Time parsetime(std::string_view str) {
  std::string_view::size_type pos = 0;
  if (str.size() < 1) throw std::runtime_error("Invalid ISO8601 time");
  if (str.front() == 'T') str.remove_prefix(1);

  // Hours
  auto [hour, hour_fractional] = readfractime(str, pos);
  std::cout << "HOUR = " << hour << "\n";
  // Minutes
  bool extended_format = false;
  str = str.substr(pos);
  if (!hour_fractional) {
    // Check if we have HH:MM or HHMM
    if (str.size() > 0 && str[0] == ':')  {
      extended_format = true;
      str.remove_prefix(1);
    }

  }

  return Time{};
}

