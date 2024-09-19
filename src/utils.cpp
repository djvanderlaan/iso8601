#include "utils.h"

#include<stdexcept>

std::string_view::size_type find_from_table(const std::string_view& str, std::string_view table) {
  for (std::string_view::size_type i = 0; str.size(); ++i) 
    for (const char& c: table) if (str[i] == c) return i;
  return std::string_view::npos;
}

std::string_view::size_type find_non_num(const std::string_view& str) {
  for (std::string_view::size_type i = 0; str.size(); ++i) 
    if (str[i] < '0' || str[i] > '9') return i;
  return std::string_view::npos;
}

bool all_num(const std::string_view& str) {
  bool num = true;
  for (const char& c: str) num &= (c >= '0' && c <= '9');
  return num;
}

int strtoint(const std::string_view& str) {
  if (str.size() == 0)
    throw std::runtime_error("Convertion to int failed.");
  std::string_view::const_iterator p = str.begin();
  // check if we start with a sign
  int sign = 1L;
  if (str.front() == '+' || str.front() == '-') {
    if (str.front() == '-') sign = -1;
    ++p;
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
  return sign * value;
}
