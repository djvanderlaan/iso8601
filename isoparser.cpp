#include<iostream>
#include<iomanip>
#include<array>
#include<string_view>
#include<cctype>
#include<stdexcept>
#include<string>
#include<cmath>

//##include "time.h"

std::string_view::size_type find_from_table(const std::string_view& str, std::string_view table);
bool all_num(const std::string_view& str);
std::string_view::size_type find_non_num(const std::string_view& str);

void parse_date(const std::string_view& str);
void parse_time(std::string_view str);

int main(int argc, char* argv[]) {

  constexpr size_t BUFSIZE = 1024;
  std::array<char, BUFSIZE> buffer;

  while (std::cin.getline(buffer.data(), BUFSIZE)) {
    std::string_view line{buffer.data()};
    // Remove starting white space
    while (!line.empty() && std::isspace(line.front())) {
      line.remove_prefix(1);
    }
    // Skip empty lines
    if (line.empty()) continue;
    std::cout << "Parsing '" << line << "'\n";
    // Now we need to determine what we have here:
    // If it starts with T or has a format hh:mm... it is a time
    // Durations always start with P
    // Otherwise is should be a date
    if (line.front() == 'T' || (line.size() >= 3 && line[2] == ':')) {
      std::cout << "TIME" << "\n";
      auto end_pos = find_from_table(line, "/P ");
      try{
        parse_time(line.substr(0, end_pos));
      } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
      }
    } else if (line.front() == 'P') {
      std::cout << "DURATION" << "\n";
    } else {
      std::cout << "DATE" << "\n";
      auto end_pos = find_from_table(line, "/TP ");
      try{
        parse_date(line.substr(0, end_pos));
      } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
      }
    }
  }
  return 0;
}


// ================================================================================================
// DATE PARSING

void parse_month_and_day(std::string_view str, bool pre_hyphen = false) {
  if (str.size() < 2 || !all_num(str.substr(0, 2)))
    throw std::runtime_error("Ivalid ISO8601 date");
  std::cout << "MONTH = '" << str.substr(0, 2) << "'\n";
  str.remove_prefix(2);
  if (str.size() > 0) {
    // check for hyphen for day; if month had a hyphen before; day
    // should have one too; and vice versa
    bool hyphen = str.front() == '-';
    if (hyphen != pre_hyphen) throw std::runtime_error("Ivalid ISO8601 date");
    if (hyphen) str.remove_prefix(1);
    // parse day
    if (str.size() != 2 || !all_num(str)) 
      throw std::runtime_error("Ivalid ISO8601 date");
    std::cout << "DAY = '" << str << "'\nDONE\n";
  } else {
    // YYYYMM is not valid; YYYY-MM is
    if (!pre_hyphen)
      throw std::runtime_error("Ivalid ISO8601 date");
    std::cout << "DONE\n";
  }
}

void parse_week_and_day(std::string_view str, bool pre_hyphen = false) {
  if (str.size() < 2 || !all_num(str.substr(0, 2)))
    throw std::runtime_error("Ivalid ISO8601 date");
  std::cout << "WEEK = '" << str.substr(0, 2) << "'\n";
  str.remove_prefix(2);
  if (str.size() > 0) {
    bool hyphen = str.front() == '-';
    // if -W01 then also hypen for day; if W01 then no hyphen for day
    if (hyphen != pre_hyphen) throw std::runtime_error("Ivalid ISO8601 date");
    if (hyphen) str.remove_prefix(1);
    if (str.size() != 1 || !all_num(str)) 
      throw std::runtime_error("Ivalid ISO8601 date");
    std::cout << "WEEKDAY = '" << str << "'\nDONE\n";
  } else {
    std::cout << "DONE\n";
  }
}

void parse_month_day_or_week(std::string_view str) {
  if (str.size() < 2) throw std::runtime_error("Ivalid ISO8601 date");
  bool hyphen = str.front() == '-';
  if (hyphen) str.remove_prefix(1);
  if (str.front() == 'W') {
    parse_week_and_day(str.substr(1), hyphen);
  } else if (str.size() == 3 && all_num(str)) {
    std::cout << "DAY = '" << str << "'\nDONE\n";
  } else if (str.size() >= 2) {
    parse_month_and_day(str, hyphen);
  } else throw std::runtime_error("Ivalid ISO8601 date");
}

void parse_year(std::string_view str) {
  if (str.size() < 4) throw std::runtime_error("Ivalid ISO8601 date");
  if (str.front() == '+' || str.front() == '-') {
    // We have a year +1234 or -1234; and should have nothing else
    if (str.size() != 5) throw std::runtime_error("Ivalid ISO8601 date");
    std::cout << "YEAR = '" << str << "'\nDONE\n";
  } else {
    const std::string_view year = str.substr(0, 4);
    if (!all_num(year)) throw std::runtime_error("Ivalid ISO8601 date");
    std::cout << "YEAR = '" << year << "'\n";
    if (str.size() == 4) {
      std::cout << "DONE\n";
    } else {
      parse_month_day_or_week(str.substr(4));
    }
  }
}

void parse_date(const std::string_view& str) {
  parse_year(str);
}

// ================================================================================================
// TIME PARSING

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

bool timezonestart(char c) {
  return c == 'Z' || c == '+' || c == '-';
}

void parse_timezone(std::string_view str) {
  if (str.size() == 0) {
    std::cout << "TIMEZONE: LOCAL TIME\n";
  } else if (str.size() == 1 && str.front() == 'Z') {
    std::cout << "TIMEZONE: ZULU TIME/UTC\n";
  } else if (str.front() == '-' || str.front() == '+') {
    if (str.size() < 3) throw std::runtime_error("Invalid time zone");
    int hour = strtoint(str.substr(0,3));
    int minutes = 0;
    if (str.size() == 3) {
      // do nothing; hours is already parsed
    } else if (str.size() == 5) {
      minutes = strtoint(str.substr(3,5));
    } else if (str.size() == 6) {
      minutes = strtoint(str.substr(4,6));
    } else {
      throw std::runtime_error("Invalid time zone");
    }
    std::cout << "TIMEZONE: " << hour << ':' << minutes << '\n';
  } else {
    throw std::runtime_error("Invalid time zone");
  }
}

void parse_fraction(std::string_view str) {
  auto end = find_non_num(str);
  std::string_view fraction_str = str.substr(0, end);
  double fraction = std::pow(10.0, -1.0*fraction_str.size()) * strtoint(fraction_str);
  std::cout << "FRACTION = " << fraction << "\n";
  if (end < str.size()) 
    parse_timezone(str.substr(end));
}

void parse_seconds(std::string_view str) {
  if (str.size() < 2) throw std::runtime_error("Invalid ISO8601 time");
  bool colonseparated = str.front() == ':';
  if (colonseparated) str.remove_prefix(1);
  if (str.size() < 2) throw std::runtime_error("Invalid ISO8601 time");
  std::string_view seconds = str.substr(0, 2);
  if (!all_num(seconds)) throw std::runtime_error("Invalid ISO8601 time");
  std::cout << "SECONDS = '" << seconds << "'\n";
  str.remove_prefix(2);
  if (str.size() > 0 && str.front() == '.') {
    str.remove_prefix(1);
    parse_fraction(str);
  } else {
    parse_timezone(str);
  }
}

void parse_minutes(std::string_view str) {
  if (str.size() < 2) throw std::runtime_error("Invalid ISO8601 time");
  bool colonseparated = str.front() == ':';
  if (colonseparated) str.remove_prefix(1);
  if (str.size() < 2) throw std::runtime_error("Invalid ISO8601 time");
  std::string_view minutes = str.substr(0, 2);
  if (!all_num(minutes)) throw std::runtime_error("Invalid ISO8601 time");
  std::cout << "MINUTES = '" << minutes << "'\n";
  str.remove_prefix(2);
  // check for fractional minutes
  if (str.size() > 0 && str.front() == '.') {
    str.remove_prefix(1);
    parse_fraction(str);
  // check if we have the start of a time zone
  } else if (str.size() > 0 && timezonestart(str.front())) {
    parse_timezone(str);
  // if we have characters left this should be seconds
  } else if (str.size() > 0) {
    if (colonseparated != (str.front() == ':'))
      throw std::runtime_error("Invalid ISO8601 time");
    parse_seconds(str);
  } else {
    parse_timezone(str);
  }
}

void parse_hour(std::string_view str) {
  if (str.size() < 2) throw std::runtime_error("Invalid ISO8601 time");
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
  }
}

void parse_time(std::string_view str) {
  if (str.front() == 'T') str.remove_prefix(1);
  parse_hour(str);
}

// ================================================================================================
// GENERIC UTILS
//
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

