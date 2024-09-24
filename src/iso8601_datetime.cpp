
#include "iso8601_datetime.h"

namespace ISO8601 {

  std::ostream& operator<<(std::ostream& stream, const Datetime& datetime) {
    stream << datetime.date() << datetime.time();
    return stream;
  }


}
