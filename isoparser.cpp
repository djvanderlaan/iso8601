

#include "utils.h"
#include "parsetime.h"
#include "parsedate.h"

#include <iostream>
#include <array>


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
        auto date = parsedate(line.substr(0, end_pos));
        std::cout << date << '\n';
      } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
      }
    }
  }
  return 0;
}

