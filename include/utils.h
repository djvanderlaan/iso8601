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

#endif
