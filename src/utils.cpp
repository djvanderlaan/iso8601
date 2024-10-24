#include "utils.h"

#include<stdexcept>

namespace ISO8601 {

  std::string_view::size_type find_from_table(const std::string_view str, const std::string_view table) {
    for (std::string_view::size_type i = 0; str.size(); ++i) 
      for (const char& c: table) if (str[i] == c) return i;
    return std::string_view::npos;
  }

  std::string_view::size_type count_numeric(const std::string_view str) {
    for (std::string_view::size_type i = 0; str.size(); ++i) 
      if (!isnumchar(str[i])) return i;
    return str.size();
  }

  int strtoint(const std::string_view str) {
    if (str.size() == 0)
      throw std::runtime_error("Convertion to int failed.");
    std::string_view::const_iterator p = str.begin();
    // check if we start with a sign
    int sign = 1L;
    unsigned int ncharsign = 0;
    if (str.front() == '+' || str.front() == '-') {
      if (str.front() == '-') sign = -1;
      ++p;
      if (str.size() == 1)
        throw std::runtime_error("Convertion to int failed.");
    } else if ( (ncharsign = starts_with(str, "±")) ) {
      sign = 0;
      p += ncharsign;
      if (str.size() == 1)
        throw std::runtime_error("Convertion to int failed.");
    }
    // the remainder should be a number
    int value = 0L;
    for ( ; p != str.end(); ++p) {
      char c = *p;
      switch (c) {
        case '0':
          value = value*10L + 0L;
          break;
        case '1':
          value = value*10L + 1L;
          break;
        case '2':
          value = value*10L + 2L;
          break;
        case '3':
          value = value*10L + 3L;
          break;
        case '4':
          value = value*10L + 4L;
          break;
        case '5':
          value = value*10L + 5L;
          break;
        case '6':
          value = value*10L + 6L;
          break;
        case '7':
          value = value*10L + 7L;
          break;
        case '8':
          value = value*10L + 8L;
          break;
        case '9':
          value = value*10L + 9L;
          break;
        default:
          throw std::runtime_error("Convertion to int failed.");
      }
    }
    if (value != 0 && sign == 0) 
      throw std::runtime_error("Convertion to int failed.");
    return sign * value;
  }

}
