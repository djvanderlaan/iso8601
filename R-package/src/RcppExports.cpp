// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// rcpp_parse_iso_dateframe
List rcpp_parse_iso_dateframe(CharacterVector in_str, int transformdate);
RcppExport SEXP _iso8601_rcpp_parse_iso_dateframe(SEXP in_strSEXP, SEXP transformdateSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type in_str(in_strSEXP);
    Rcpp::traits::input_parameter< int >::type transformdate(transformdateSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_parse_iso_dateframe(in_str, transformdate));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_parse_datetime
List rcpp_parse_datetime(CharacterVector in_str, bool fillmissing);
RcppExport SEXP _iso8601_rcpp_parse_datetime(SEXP in_strSEXP, SEXP fillmissingSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type in_str(in_strSEXP);
    Rcpp::traits::input_parameter< bool >::type fillmissing(fillmissingSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_parse_datetime(in_str, fillmissing));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_parse_time
NumericVector rcpp_parse_time(CharacterVector in_str);
RcppExport SEXP _iso8601_rcpp_parse_time(SEXP in_strSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type in_str(in_strSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_parse_time(in_str));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_standardise
CharacterVector rcpp_standardise(CharacterVector in_str, bool fillmissing, bool toymd, bool to_zulu);
RcppExport SEXP _iso8601_rcpp_standardise(SEXP in_strSEXP, SEXP fillmissingSEXP, SEXP toymdSEXP, SEXP to_zuluSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type in_str(in_strSEXP);
    Rcpp::traits::input_parameter< bool >::type fillmissing(fillmissingSEXP);
    Rcpp::traits::input_parameter< bool >::type toymd(toymdSEXP);
    Rcpp::traits::input_parameter< bool >::type to_zulu(to_zuluSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_standardise(in_str, fillmissing, toymd, to_zulu));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_type
IntegerVector rcpp_type(CharacterVector in_str);
RcppExport SEXP _iso8601_rcpp_type(SEXP in_strSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type in_str(in_strSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_type(in_str));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_iso8601_rcpp_parse_iso_dateframe", (DL_FUNC) &_iso8601_rcpp_parse_iso_dateframe, 2},
    {"_iso8601_rcpp_parse_datetime", (DL_FUNC) &_iso8601_rcpp_parse_datetime, 2},
    {"_iso8601_rcpp_parse_time", (DL_FUNC) &_iso8601_rcpp_parse_time, 1},
    {"_iso8601_rcpp_standardise", (DL_FUNC) &_iso8601_rcpp_standardise, 4},
    {"_iso8601_rcpp_type", (DL_FUNC) &_iso8601_rcpp_type, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_iso8601(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}