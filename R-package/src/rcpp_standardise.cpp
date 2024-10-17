#include <Rcpp.h>
#include <sstream>
#include <iomanip>

#include "iso8601.h"

using namespace Rcpp;


// [[Rcpp::export]]
CharacterVector rcpp_standardise(CharacterVector in_str, 
    bool fillmissing = true, bool toymd = true, bool to_zulu = true) {
  CharacterVector result(in_str.size(), CharacterVector::get_na());
  std::ostringstream ostream; 
  for (R_xlen_t i = 0, iend = in_str.size(); i < iend; ++i) {
    if (!CharacterVector::is_na(in_str[i])) {
      const std::string_view str{in_str[i]};
      ISO8601::ISO8601Type type = ISO8601::determinetype(str);
      ostream.str("");
      try {
        switch (type) {
          case ISO8601::ISO8601Type::Date: {
              ISO8601::Date d = ISO8601::parsedate(str);
              if (fillmissing) d = ISO8601::fillmissing(d);
              if (toymd && d.type() != ISO8601::Date::YEARMONTHDAY) 
                d = toyearmonthday(d);
              ostream << d << std::ends;
              result[i] = ostream.str();
          }
          break;
          case ISO8601::ISO8601Type::Time: {
              ISO8601::Time t = ISO8601::parsetime(str);
              if (fillmissing) t = ISO8601::fillmissing(t);
              t.set_timezone(ISO8601::Timezone{});
              ostream << t << std::ends;
              result[i] = ostream.str();
          }
          break;
          case ISO8601::ISO8601Type::Datetime: {
              ISO8601::Datetime dt = ISO8601::parsedatetime(str);
              if (fillmissing) dt = ISO8601::fillmissing(dt);
              if (toymd && dt.date().type() != ISO8601::Date::YEARMONTHDAY) 
                dt.date( toyearmonthday(dt.date()) );
              if (to_zulu) dt = tozulu(dt);
              ostream << dt << std::ends;
              result[i] = ostream.str();
          }
          break;
          case ISO8601::ISO8601Type::Duration:
            warning("Durations not yet supported. Returning NA.");
            break;
          case ISO8601::ISO8601Type::TimeInterval:
            warning("Time intervals not yet supported. Returning NA.");
            break;
          case ISO8601::ISO8601Type::RepeatingInterval:
            warning("Repeating intervals not yet supported. Returning NA.");
            break;
        }
      } catch(const std::exception& e) {
        warning("Parsing of '%s' failed. Returning NA.", str);
      }
    }
  }
  return result;
}

