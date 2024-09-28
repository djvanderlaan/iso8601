
#' @useDynLib iso8601
#' @import Rcpp
#' @importFrom Rcpp evalCpp
#' @export
test <- function() {
  rcpp_test(0)
}
