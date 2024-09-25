#include "iso8601.h"
#include "utils.h"

namespace ISO8601 {

  ISO8601Type determinetype(std::string_view str) {
    if (contains(str, '/')) return ISO8601Type::TimeInterval;
    if (starts_with(str, 'P')) return ISO8601Type::Duration;
    if (starts_with(str, 'R')) return ISO8601Type::RepeatingInterval;
    if (starts_with(str, 'T') || (str.size() > 2 && str[2] == ':'))
      return ISO8601Type::Time;
    // we now have either a date or datetime; a datetime can either be
    // <data>T<time> or <date> <time>; officially only T is allowed
    if (contains(str, 'T') || contains(str, ' ')) return ISO8601Type::DateTime;
    return ISO8601Type::Date;
  }

}
