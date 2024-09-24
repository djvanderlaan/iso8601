#include "iso8601.h"
#include "utils.h"

ISO8601datetime parsedatetime(std::string_view str) {
  const auto date_end_pos = find_from_table(str, "T ");
  ISODate date = parsedate(str.substr(0, date_end_pos));
  str.remove_prefix(date_end_pos);
  if (str.size() < 1 || str.front() == '/') 
    throw std::runtime_error("Invalid ISO8601 date-time");
  if (str.front() == ' ') str.remove_prefix(1);
  ISOTime time = parsetime(str);
  return ISO8601datetime(date, time);
}


