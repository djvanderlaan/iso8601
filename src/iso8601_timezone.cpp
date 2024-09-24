#include "iso8601_timezone.h"
#include <iomanip>
#include <cmath>


namespace ISO8601 {


  std::ostream& operator<<(std::ostream& stream, const Timezone& tz) {
    if (tz.localtime()) {
      // do nothing
    } else if (tz.offset_hours() == 0 && tz.offset_minutes() == 0) {
      stream << 'Z';
    } else {
      if (tz.offset_hours() < 0) stream << '-'; else stream << '+';
      stream << std::setw(2) << std::setfill('0') << std::abs(tz.offset_hours());
      stream << ':' << std::setw(2) << std::setfill('0') << tz.offset_minutes();
    }
    return stream;
  }


}

