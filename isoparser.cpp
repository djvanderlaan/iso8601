#include "utils.h"
#include "iso8601.h"

#include <iostream>
#include <array>

enum class ISOType { Date, Time, DateTime, Duration, TimeInterval, RepeatingInterval };

ISOType determineisotype(const std::string_view& str) {
  if (contains(str, '/')) return ISOType::TimeInterval;
  if (starts_with(str, 'P')) return ISOType::Duration;
  if (starts_with(str, 'R')) return ISOType::RepeatingInterval;
  if (starts_with(str, 'T') || (str.size() > 2 && str[2] == ':'))
    return ISOType::Time;
  // we now have either a date or datetime; a datetime can either be
  // <data>T<time> or <date> <time>; officially only T is allowed
  if (contains(str, 'T') || contains(str, ' ')) return ISOType::DateTime;
  return ISOType::Date;
}

std::pair<ISODate, ISOTime> parsedatetime(std::string_view str) {
  const auto date_end_pos = find_from_table(str, "/TP ");
  ISODate date = parsedate(str.substr(0, date_end_pos));
  // Wee need a full date; check for that
  switch (date.type()) {
    case ISODate::YEAR:
      throw std::runtime_error("Invalid ISO8601 date-time");
    case ISODate::YEARMONTHDAY:
      if (!date.has_month() || !date.has_day())
        throw std::runtime_error("Invalid ISO8601 date-time");
      break;
    case ISODate::YEARWEEKDAY:
      if (!date.has_week() || !date.has_weekday())
        throw std::runtime_error("Invalid ISO8601 date-time");
      break;
    case ISODate::YEARDAY:
      if (!date.has_yearday())
        throw std::runtime_error("Invalid ISO8601 date-time");
      break;
  }
  str.remove_prefix(date_end_pos);
  if (str.size() < 1 || str.front() == '/') 
    throw std::runtime_error("Invalid ISO8601 date-time");
  if (str.front() == ' ') str.remove_prefix(1);
  ISOTime time = parsetime(str);
  return std::make_pair(date, time);
}



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
    try {
      const auto dt = parsedatetime(line);
      std::cout << dt.first << dt.second << "\n";
    } catch (std::exception& e) {
      std::cout << "<invalid>\n";
      //std::cerr << e.what() << "\n";
    }

    /*
    //std::cout << "Parsing '" << line << "'\n";
    // Now we need to determine what we have here:
    // If it starts with T or has a format hh:mm... it is a time
    // Durations always start with P
    // Otherwise is should be a date
    if (line.front() == 'T' || (line.size() >= 3 && line[2] == ':')) {
      //std::cout << "TIME" << "\n";
      auto end_pos = find_from_table(line, "/P ");
      try{
        auto time = parsetime(line.substr(0, end_pos));
        time = make_standard(time, true);
        std::cout << time << "\n";
      } catch (std::exception& e) {
        std::cout << "<invalid>\n";
        //std::cerr << e.what() << "\n";
      }
    } else if (line.front() == 'P') {
      std::cout << "DURATION" << "\n";
    } else {
      //std::cout << "DATE" << "\n";
      auto end_pos = find_from_table(line, "/TP ");
      try{
        auto date = parsedate(line.substr(0, end_pos));
        std::cout << date << '\n';
      } catch (std::exception& e) {
        std::cout << "<invalid>\n";
        //std::cerr << e.what() << "\n";
      }
    }
    */
  }
  return 0;
}

