#include <Rcpp.h>
#include <sstream>
#include <iomanip>
#include "iso8601.h"

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector rcpp_parse_time(CharacterVector in_str) {
  NumericVector seconds(in_str.size());
  for (R_xlen_t i = 0, iend = in_str.size(); i < iend; ++i) {
    try {
      if (!CharacterVector::is_na(in_str[i])) {
        const std::string_view str{in_str[i]};
        // With the second argument true we indicate that do not require that
        // times start with T; we are parsing times so we know that we can 
        // expect times. Otherwise 121410 would by invalid (could also be the
        // year 1214 and month 10)
        ISO8601::Time t = ISO8601::parsetime(str, true);
        t = ISO8601::fillmissing(t);
        seconds[i] = t.hour() * 3600.0 + t.minutes() * 60.0 + t.seconds();
      } else {
        seconds[i] = NumericVector::get_na();
      }
    } catch(const std::exception& e) {
      seconds[i] = NumericVector::get_na();
    }
  }
  return seconds;
}

