#include <Rcpp.h>

#include "iso8601.h"

using namespace Rcpp;


// [[Rcpp::export]]
IntegerVector rcpp_test(IntegerVector a) {
  return 0;
}

// [[Rcpp::export]]
IntegerVector rcpp_parse(CharacterVector str) {
  for (int i = 0; i < str.size(); ++i) {
    const char* c = str[i].get_cstring();
    std::cout << c << "\n";
  }
}
