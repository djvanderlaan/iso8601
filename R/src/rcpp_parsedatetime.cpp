#include <Rcpp.h>
#include <sstream>
#include <iomanip>
#include "iso8601.h"

using namespace Rcpp;


// [[Rcpp::export]]
List rcpp_parse_datetime(CharacterVector in_str, 
    bool fillmissing = true) {

  IntegerVector year(in_str.size());
  IntegerVector month(in_str.size());
  IntegerVector day(in_str.size());
  IntegerVector hour(in_str.size());
  IntegerVector minutes(in_str.size());
  NumericVector seconds(in_str.size());
  CharacterVector timezone(in_str.size());

  std::ostringstream ostream;  // needed to convert timezone
  for (R_xlen_t i = 0, iend = in_str.size(); i < iend; ++i) {
    ostream.str("");
    try {
      if (!CharacterVector::is_na(in_str[i])) {
        const std::string_view str{in_str[i]};
        ISO8601::Datetime dt = ISO8601::parsedatetime(str);
        if (dt.date().type() != ISO8601::Date::YEARMONTHDAY) 
          dt.date( toyearmonthday(dt.date()) );
        if (fillmissing) dt.time(ISO8601::fillmissing(dt.time())); else
          dt.time(ISO8601::removefractions(dt.time()));
        // get time zone before converting to zulu
        ostream << dt.time().timezone() << std::ends;
        timezone[i] = ostream.str();
        dt = tozulu(dt);
        year[i] = dt.date().year();
        month[i] = dt.date().month();
        day[i] = dt.date().day();
        hour[i] = dt.time().hour();
        minutes[i] = dt.time().has_minutes() ? dt.time().minutes() : IntegerVector::get_na();
        seconds[i] = dt.time().has_seconds() ? dt.time().seconds() : NumericVector::get_na(); 
      } else {
        year[i] = IntegerVector::get_na();
        month[i] = IntegerVector::get_na();
        day[i] = IntegerVector::get_na();
        hour[i] = IntegerVector::get_na();
        minutes[i] = IntegerVector::get_na();
        seconds[i] = NumericVector::get_na();
        timezone[i] = CharacterVector::get_na();
      }
    } catch(const std::exception& e) {
      year[i] = IntegerVector::get_na();
      month[i] = IntegerVector::get_na();
      day[i] = IntegerVector::get_na();
      hour[i] = IntegerVector::get_na();
      minutes[i] = IntegerVector::get_na();
      seconds[i] = NumericVector::get_na();
      timezone[i] = CharacterVector::get_na();
    }
  }
  return List::create(
        Named("sec") = seconds,
        Named("min") = minutes,
        Named("hour") = hour,
        Named("mday") = day,
        Named("mon") = month,
        Named("year") = year,
        Named("zone") = timezone
      );
}

