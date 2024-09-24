#include "iso8601.h"

#include <iostream>
#include <array>


int main(int argc, char* argv[]) {

  constexpr size_t BUFSIZE = 1024;
  std::array<char, BUFSIZE> buffer;

  while (std::cin.getline(buffer.data(), BUFSIZE)) {
    std::string_view line{buffer.data()};
    // Remove starting white space
    while (!line.empty() && std::isspace(line.front())) 
      line.remove_prefix(1);
    while (!line.empty() && std::isspace(line.back())) 
      line.remove_suffix(1);
    // Skip empty lines
    if (line.empty()) continue;
    std::cout << "Parsing '" << line << "'\n";
    try {
      const auto dt = ISO8601::parsedatetime(line);
      std::cout << dt << "\n";
    } catch (std::exception& e) {
      std::cout << "<invalid>\n";
      //std::cerr << e.what() << "\n";
    }
  }
  return 0;
}

