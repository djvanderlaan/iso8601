#include "iso8601.h"
#include "utils.h"

namespace ISO8601 {

ISOType determineisotype(std::string_view str) {
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

}
