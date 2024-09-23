#ifndef utils_h
#define utils_h

#include<string_view>


std::string_view::size_type find_from_table(const std::string_view& str, std::string_view table);

bool all_num(const std::string_view& str);

std::string_view::size_type find_non_num(const std::string_view& str);

int strtoint(const std::string_view& str);

std::string_view::size_type count_numeric(const std::string_view& str);

constexpr bool isnumchar(char c) {
  return (c >= '0' && c <= '9');
}

constexpr bool isdecimal(char c) {
  return c == '.' || c == ',';
}

inline bool starts_with(const std::string_view& str, const std::string_view& x) {
  if (str.size() < x.size()) return false;
  bool result = true;
  for (auto i = 0UL; i < x.size(); ++i) 
    if (x[i] != str[i]) result = false;
  return result;
}

constexpr bool starts_with(const std::string_view& str, char x) {
  return str.size() > 0 && str.front() == x;
}

constexpr bool contains(std::string_view str, char c) {
  return str.find(c) != std::string_view::npos;
}


#endif
