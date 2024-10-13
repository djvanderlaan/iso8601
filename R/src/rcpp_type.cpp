#include <Rcpp.h>
#include "iso8601.h"

using namespace Rcpp;


int rcpp_date_type(const ISO8601::Date& d) {
  switch (d.type()) {
    case ISO8601::Date::YEAR:
      return 1;
    case ISO8601::Date::YEARMONTHDAY:
      if (!d.has_month()) {
        return 1;
      } else if (!d.has_day()) {
        return 2;
      } else {
        return 3;
      }
    case ISO8601::Date::YEARWEEKDAY:
      if (!d.has_week()) {
        return 1;
      } else if (!d.has_weekday()) {
        return 4;
      } else {
        return 5;
      }
    case ISO8601::Date::YEARDAY:
      if (!d.has_yearday()) {
        return 1;
      } else {
        return 6;
      }
  }
  return 1;
}

int rcpp_timezone_type(ISO8601::Timezone tz) {
  if (tz.localtime()) return 0;
  if (tz.offset_hours() == 0 && tz.offset_minutes() == 0) return 1;
  return 2;
}

int rcpp_time_type(const ISO8601::Time& t) {
  const int tz = rcpp_timezone_type(t.timezone());
  if (!t.has_minutes()) return tz + 10L;
  if (t.minutes_fractional()) return tz*10L + 20L;
  if (!t.has_seconds()) return tz + 30L;
  if (t.seconds_fractional()) return tz + 40L;
  return tz + 50L;
}


int rcpp_determine_type(std::string_view str) {
  ISO8601::ISO8601Type type = ISO8601::determinetype(str);
  try {
    switch (type) {
      case ISO8601::ISO8601Type::Date: 
        return rcpp_date_type(ISO8601::parsedate(str))*100;
      case ISO8601::ISO8601Type::Time: 
        return rcpp_time_type(ISO8601::parsetime(str));
      case ISO8601::ISO8601Type::Datetime: {
        const auto dt = ISO8601::parsedatetime(str);
        return rcpp_date_type(dt.date())*100 + rcpp_time_type(dt.time());
      }
      case ISO8601::ISO8601Type::Duration:
        return 1000;
      case ISO8601::ISO8601Type::TimeInterval:
        return 2000;
      case ISO8601::ISO8601Type::RepeatingInterval:
        return 3000;
    }
  } catch (std::exception& e) {
    warning("Parsing of '%s' failed. Returning NA.", str);
  }
  return NA_INTEGER;
}


// [[Rcpp::export]]
IntegerVector rcpp_type(CharacterVector in_str) {
  IntegerVector res(in_str.size());
  for (R_xlen_t i = 0, iend = in_str.size(); i < iend; ++i) {
    if (CharacterVector::is_na(in_str[i])) { 
      res[i] = NA_INTEGER;
    } else {
      const std::string_view str{in_str[i]};
      res[i] = rcpp_determine_type(str);
    }
  }
  return res;
}
