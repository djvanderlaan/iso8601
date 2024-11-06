#ifndef iso8601_h
#define iso8601_h

#include "iso8601_date.h"
#include "iso8601_time.h"
#include "iso8601_datetime.h"
#include <string_view>

namespace ISO8601 {

  enum class ISO8601Type { Date, Time, Datetime, Duration, TimeInterval, RepeatingInterval };
  ISO8601Type determinetype(std::string_view str);

  Date parsedate(std::string_view str);
  Time parsetime(std::string_view str, bool noTisok = false);
  Datetime parsedatetime(std::string_view str);

}

#endif

