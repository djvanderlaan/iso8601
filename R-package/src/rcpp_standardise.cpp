#include <Rcpp.h>
#include <sstream>
#include <iomanip>

#include "iso8601.h"

using namespace Rcpp;


// [[Rcpp::export]]
CharacterVector rcpp_standardise_datetime(CharacterVector in_str, 
    bool fillmissing = true, bool toymd = true, bool to_zulu = true) {
  CharacterVector result(in_str.size());
  std::ostringstream ostream; 
  for (R_xlen_t i = 0, iend = in_str.size(); i < iend; ++i) {
    ostream.str("");
    try {
      if (!CharacterVector::is_na(in_str[i])) {
        const std::string_view str{in_str[i]};
        ISO8601::Datetime dt = ISO8601::parsedatetime(str);
        if (fillmissing) dt = ISO8601::fillmissing(dt);
        if (toymd && dt.date().type() != ISO8601::Date::YEARMONTHDAY) 
          dt.date( toyearmonthday(dt.date()) );
        if (to_zulu) dt = tozulu(dt);
        ostream << dt << std::ends;
        result[i] = ostream.str();
      } else {
        result[i] = CharacterVector::get_na();
      }
    } catch(const std::exception& e) {
      result[i] = CharacterVector::get_na();
    }
  }
  return result;
  //return DataFrame::create(
        //Named("datetime") = result,
        //Named("type") = datetype
      //);
}

