#ifndef iso8601_h
#define iso8601_h

#include "iso8601_date.h"
#include "iso8601_time.h"
#include "iso8601_datetime.h"
#include <string_view>

namespace ISO8601 {

  enum class ISOType { Date, Time, DateTime, Duration, TimeInterval, RepeatingInterval };
  ISOType determineisotype(std::string_view str);

  Date parsedate(std::string_view str);
  Time parsetime(std::string_view str);
  Datetime parsedatetime(std::string_view str);

}

#endif
