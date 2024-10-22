#ifndef utils_h
#define utils_h

#include<string_view>

namespace ISO8601 {


  std::string_view::size_type find_from_table(const std::string_view str, 
      const std::string_view table);

  int strtoint(const std::string_view str);

  std::string_view::size_type count_numeric(const std::string_view str);

  constexpr bool isnumchar(char c) {
    return (c >= '0' && c <= '9');
  }

  constexpr bool isdecimal(char c) {
    return c == '.' || c == ',';
  }

  // Checks if the string 'str' starts with the string 'x'. If not the function
  // returns 0 otherwise it returns the length of 'x', e.g. the number of 
  // characters that match.
  inline int starts_with(const std::string_view str, const std::string_view x) {
    if (str.size() < x.size()) return 0;
    bool result = true;
    for (auto i = 0UL; i < x.size(); ++i) 
      if (x[i] != str[i]) result = false;
    return result ? x.size() : 0;
  }

  // Checks if the string 'str' starts with the character 'x'. If not the
  // function returns 0 otherwise it returns the length of 'x', e.g. the number
  // of characters that match.
  inline int starts_with(const std::string_view str, char x) {
    return str.size() > 0 && str.front() == x ? 1 : 0;
  }

  // Checks if the string 'str' contains the string 'x'. 
  inline bool contains(const std::string_view str, const std::string_view x) {
    if (x.size() == 0) return true;
    if (str.size() < x.size()) return false;
    for (auto i = 0UL; i < str.size(); ++i) {
      if (str[i] == x[0]) {
        auto m = starts_with(str.substr(i), x);
        if (m) return true;
      }
    }
    return false;
  }

  // Checks if the string 'str' contains the character 'x'. 
  inline bool contains(const std::string_view str, char c) {
    return str.find(c) != std::string_view::npos;
  }

}

#endif
