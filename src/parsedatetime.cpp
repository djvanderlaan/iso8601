#include "iso8601.h"
#include "utils.h"

namespace ISO8601 {

  Datetime parsedatetime(std::string_view str, unsigned int extrayearlen) {
    auto date_end_pos = find_from_table(str, "T ");
    if (date_end_pos == std::string_view::npos) date_end_pos = str.length();
    Date date = parsedate(str.substr(0, date_end_pos), extrayearlen);
    str.remove_prefix(date_end_pos);
    if (str.size() < 1 || str.front() == '/') 
      throw std::runtime_error("Invalid ISO8601 date-time");
    if (str.front() == ' ') str.remove_prefix(1);
    Time time = parsetime(str);
    return Datetime(date, time);
  }

}
