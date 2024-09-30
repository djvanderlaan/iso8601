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
CharacterVector rcpp_parse(CharacterVector in_str) {
  CharacterVector result{in_str.size()};
  for (R_xlen_t i = 0, iend = in_str.size(); i < iend; ++i) {
    std::ostringstream ostream; // dynamic buffer
    try {
      if (!CharacterVector::is_na(in_str[i])) {
        const std::string_view str{in_str[i]};
        ISO8601::Datetime dt = ISO8601::parsedatetime(str);
        ostream << dt << std::ends;
        result[i] = ostream.str();
        //s1 << 1 << ' ' << 3.14 << " example\n" << std::ends;
        //std::cout << dt << "\n";
      } else {
        result[i] = CharacterVector::get_na();
      }
    } catch(const std::exception& e) {
    result[i] = CharacterVector::get_na();
    }
  }
  return result;
}

/*
int rcpp_parse(NumericVector str) {
  for (int i = 0; i < str.size(); ++i) {
    const double s = str.at(i);
    //const char* c = str[i];
    //std::cout << c << "\n";
  }
  return 0;
}
*/
