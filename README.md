# ISO8601

Parser for ISO8601 dates, times, and date-times. The parse will detect the type
and generate appropiate objects containing the date and time information.

The c++ code is also used in the `iso8601` R-package. The source and
documentation of this package can be found in the 
[R-package subdirectory](R-package/).

Some example code:

```cpp
#include <iso8601.h>
#include <iostream>

int main() {

  ISO8601::Date date = ISO8601::parsedate("2030-W01-3");
  std::cout << date << '\n';

  ISO8601::Time time = ISO8601::parsetime("14:45");
  std::cout << time << '\n';

  ISO8601::Datetime datetime = ISO8601::parsedatetime("20300405T1445+01");
  std::cout << datetime << '\n';

  const std::string str{"2030-123"};
  ISO8601::ISO8601Type type = ISO8601::determinetype(str);
  switch (type) {
    case ISO8601::ISO8601Type::Date:
      std::cout << str << " is a Date\n"; 
      break;
    case ISO8601::ISO8601Type::Time:
      std::cout << str << " is a Time\n"; 
      break;
    case ISO8601::ISO8601Type::Datetime:
      std::cout << str << " is a Datetime\n"; 
      break;
    case ISO8601::ISO8601Type::Duration:
      std::cout << str << " is a Duration\n"; 
      break;
    case ISO8601::ISO8601Type::TimeInterval:
      std::cout << str << " is a TimeInterval\n"; 
      break;
    case ISO8601::ISO8601Type::RepeatingInterval:
      std::cout << str << " is a RepeatingInterval\n"; 
      break;
  }

  return 0;
}
```

