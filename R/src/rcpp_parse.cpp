#include <Rcpp.h>

#include <sstream>
#include <iomanip>

#include "iso8601.h"

using namespace Rcpp;


// [[Rcpp::export]]
IntegerVector rcpp_test(IntegerVector a) {
  return 0;
}

// [[Rcpp::export]]
DataFrame rcpp_standardise_datetime(CharacterVector in_str, 
    bool fill_missing = true, bool to_ymd = true, bool to_zulu = true) {
  CharacterVector result(in_str.size());
  IntegerVector datetype(in_str.size());
  std::ostringstream ostream; 
  for (R_xlen_t i = 0, iend = in_str.size(); i < iend; ++i) {
    ostream.str("");
    try {
      if (!CharacterVector::is_na(in_str[i])) {
        const std::string_view str{in_str[i]};
        ISO8601::Datetime dt = ISO8601::parsedatetime(str);
        if (fill_missing) dt = ISO8601::fillmissing(dt);
        if (to_ymd && dt.date().type() != ISO8601::Date::YEARMONTHDAY) 
          dt.date( toyearmonthday(dt.date()) );
        if (to_zulu) dt = tozulu(dt);
        ostream << dt << std::ends;
        result[i] = ostream.str();
        switch (dt.date().type()) {
          case ISO8601::Date::YEAR:
            datetype[i] = 1;
            break;
          case ISO8601::Date::YEARMONTHDAY:
            datetype[i] = 2;
            break;
          case ISO8601::Date::YEARWEEKDAY:
            datetype[i] = 3;
            break;
          case ISO8601::Date::YEARDAY:
            datetype[i] = 4;
            break;
        }
      } else {
        result[i] = CharacterVector::get_na();
      }
    } catch(const std::exception& e) {
      result[i] = CharacterVector::get_na();
    }
  }
  return DataFrame::create(
        Named("datetime") = result,
        Named("type") = datetype
      );
}

