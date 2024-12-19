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
    ISO8601::ISO8601Type type = ISO8601::determinetype(line);
    try {
      switch (type) {
        case ISO8601::ISO8601Type::Date: {
          const auto d = ISO8601::parsedate(line);
          std::cout << d << "\n";
          //break;
        }
        case ISO8601::ISO8601Type::Time: {
          const auto t = ISO8601::parsetime(line);
          std::cout << t << "\n";
          //break;
        }
        case ISO8601::ISO8601Type::Datetime: {
          const auto dt = ISO8601::parsedatetime(line);
          std::cout << dt << "\n";
          break;
        }
        case ISO8601::ISO8601Type::Duration: {
          std::cout << "foo\n";
          auto p = ISO8601::parseduration(line);
          std::cout << p << "\n";
          std::cout << "foo\n";
          //p = standardise(p);
          //p = removefractions(p);
          p = simplify(p);
          std::cout << "bar\n";
          std::cout << p << "\n";
          break;
        }
        case ISO8601::ISO8601Type::TimeInterval:
          std::cout << "<time interval not supported>\n";
          break;
        case ISO8601::ISO8601Type::RepeatingInterval:
          std::cout << "<repeating interval not supported>\n";
          break;
      }
    } catch (std::exception& e) {
      std::cout << "<invalid>\n";
      std::cerr << e.what() << "\n";
    }
  }
  return 0;
}

