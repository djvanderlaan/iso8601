#include <Rcpp.h>
#include <sstream>
#include <iomanip>
#include "iso8601.h"

using namespace Rcpp;


inline void rcpp_fill_date(const ISO8601::Date& d, List& res) {
  res["year"] = d.year();
  if (d.has_month()) res["month"] = d.month();
  if (d.has_day()) res["day"] = d.day();
  if (d.has_week()) res["week"] = d.week();
  if (d.has_weekday()) res["weekday"] = d.weekday();
  if (d.has_yearday()) res["yearday"] = d.yearday();
}

inline void rcpp_fill_timezone(const ISO8601::Timezone& tz, List& res) {
  if (tz.localtime()) {
    res["tz_localtime"] = tz.localtime();
  } else {
    res["tz_offset_hours"] = tz.offset_hours();
    res["tz_offset_minutes"] = tz.offset_minutes();
  }
}

inline void rcpp_fill_time(const ISO8601::Time& t, List& res, bool tz = true) {
  res["hour"] = t.hour();
  if (t.has_minutes()) res["minutes"] = t.minutes();
  if (t.has_seconds()) res["seconds"] = t.seconds();
  if (tz) rcpp_fill_timezone(t.timezone(), res);
}



List rcpp_parse_element_date(std::string_view str) {
  const auto d = ISO8601::parsedate(str);
  List res;
  rcpp_fill_date(d, res);
  res.attr("class") = "ISO8601Date";
  return res;
}

List rcpp_parse_element_time(std::string_view str, bool tz = true) {
  auto t = ISO8601::parsetime(str);
  t = ISO8601::removefractions(t);
  List res;
  rcpp_fill_time(t, res, false);
  res.attr("class") = "ISO8601Time";
  return res;
}

List rcpp_parse_element_datetime(std::string_view str, bool tz = true) {
  auto dt = ISO8601::parsedatetime(str);
  List res;
  rcpp_fill_date(dt.date(), res);
  rcpp_fill_time(ISO8601::removefractions(dt.time()), res, true);
  res.attr("class") = "ISO8601DateTime";
  return res;
}

List rcpp_parse_element(std::string_view str) {
  ISO8601::ISO8601Type type = ISO8601::determinetype(str);
  try {
    switch (type) {
      case ISO8601::ISO8601Type::Date: 
        return rcpp_parse_element_date(str);
      case ISO8601::ISO8601Type::Time: 
        return rcpp_parse_element_time(str, false);
      case ISO8601::ISO8601Type::Datetime: 
        return rcpp_parse_element_datetime(str, false);
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
  } catch (std::exception& e) {
    warning("Parsing of '%s' failed. Returning NA.", str);
  }
  return List();
}

// [[Rcpp::export]]
List rcpp_parse_iso_list(CharacterVector in_str) {
  List res(in_str.size());
  for (R_xlen_t i = 0, iend = in_str.size(); i < iend; ++i) {
    const std::string_view str{in_str[i]};
    res[i] = rcpp_parse_element(str);
    if (List(res[i]).size() == 0) res[i] = NA_LOGICAL;
  }
  return res;
}

