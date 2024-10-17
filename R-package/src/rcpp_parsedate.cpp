#include <Rcpp.h>
#include <sstream>
#include <iomanip>
#include "iso8601.h"

using namespace Rcpp;

// [[Rcpp::export]]
List rcpp_parse_date(CharacterVector in_str) {
  IntegerVector year(in_str.size());
  IntegerVector yearday(in_str.size());
  for (R_xlen_t i = 0, iend = in_str.size(); i < iend; ++i) {
    try {
      if (!CharacterVector::is_na(in_str[i])) {
        const std::string_view str{in_str[i]};
        ISO8601::Date d = ISO8601::parsedate(str);
        d = ISO8601::fillmissing(d);
        d = ISO8601::toyearday(d);
        year[i] = d.year();
        yearday[i] = d.yearday();
      } else {
        year[i] = IntegerVector::get_na();
        yearday[i] = IntegerVector::get_na();
      }
    } catch(const std::exception& e) {
      year[i] = IntegerVector::get_na();
      yearday[i] = IntegerVector::get_na();
    }
  }
  return List::create(
    Named("year") = year,
    Named("yearday") = yearday
  );
}

