#include<iostream>
#include<iomanip>
#include<array>
#include<string_view>
#include<cctype>
#include<stdexcept>
#include<string>
#include<cmath>

//##include "time.h"

#include "utils.h"
#include "parsetime.h"


void parse_date(const std::string_view& str);

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
        auto time = parsetime(line.substr(0, end_pos));
        std::cout << time << "\n";
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

