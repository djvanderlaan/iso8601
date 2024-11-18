#include "iso8601_duration.h"
#include "utils.h"

namespace ISO8601 {

  typedef std::pair<double, bool> Fractional;

  Fractional readfrac(const std::string_view str, std::string_view::size_type& pos) {
    pos = 0;
    // The following character should be numbers posibly one decimal sign in the 
    // middle; determine the end of the string
    bool isfraction = false;
    for ( ; pos < str.size(); ++pos) {
      const char c = str[pos];
      if (isnumchar(c)) {
        // do nothing
      } else if (!isfraction && isdecimal(c)) {
        // we stop when we get to the second decimal separator
        isfraction = true;
      } else {
        break;
      }
    }
    // Get the actual number
    std::string vstr{str.substr(0, pos)};
    // The string should start and end with a number
    if (vstr.size() == 0 || !isnumchar(str[0]) || !isnumchar(str[pos-1]))
      throw std::runtime_error("Invalid ISO8601 duration");
    // Replace , with .; stod does not understand , as decimal separator
    for (auto& c: vstr) if (isdecimal(c) && c != '.') c = '.';
    // convert
    double val = std::stod(vstr, nullptr);
    return std::make_pair(val, isfraction);
  }


  Duration parseduration(std::string_view str) {
    Duration duration{};
    // minimum length is 3, e.g. P1Y
    if (str.size() < 3 || str[0] != 'P')
      throw std::runtime_error("Invalid ISO8601 duration");
    str.remove_prefix(1);
    // Keep track if we are in date part or time part
    bool time = false;
    // Read date part; YMD
    while (str.size()) {
      if (str[0] == 'T') {
        time = true;
        str.remove_prefix(1);
        break;
      }
      std::string_view::size_type pos = 0;
      const auto r = readfrac(str, pos);
      str = str.substr(pos);
      if (str.size() < 1) throw std::runtime_error("Invalid ISO8601 duration");
      const char element = str[0];
      switch(element) {
        case 'Y':
          duration.years(r.first, r.second);
          str.remove_prefix(1);
          break;
        case 'M':
          duration.months(r.first, r.second);
          str.remove_prefix(1);
          break;
        case 'D':
          duration.days(r.first, r.second);
          str.remove_prefix(1);
          break;
        case 'W':
          duration.weeks(r.first, r.second);
          str.remove_prefix(1);
          break;
      }
    }
    // Read time part
    while (time && str.size()) {
      std::string_view::size_type pos = 0;
      const auto r = readfrac(str, pos);
      str = str.substr(pos);
      if (str.size() < 1) throw std::runtime_error("Invalid ISO8601 duration");
      const char element = str[0];
      switch(element) {
        case 'H':
          duration.hours(r.first, r.second);
          str.remove_prefix(1);
          break;
        case 'M':
          duration.minutes(r.first, r.second);
          str.remove_prefix(1);
          break;
        case 'S':
          duration.seconds(r.first, r.second);
          str.remove_prefix(1);
          break;
      }
    }
    return duration;
  }
}

