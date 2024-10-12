#' Convert date in ISO8601 format into R POSIXct object
#'
#' @param x character vector of date-time objects
#'
#' @details
#' Dates are acceptes in any of the formats supported by ISO8601.
#'
#' @return
#' Returns a \code{\link{Date}} object with the same length as \code{x}. 
#'
#' @examples
#' parsedate(c("2024-01-01", "2024-W01-1", "2024001"))
#'
#' @useDynLib iso8601
#' @import Rcpp
#' @importFrom Rcpp evalCpp
#' @export
parsedate <- function(x) {
  res <- rcpp_parse_date(x)
  fail <- is.na(res$year) & !is.na(x)
  if (any(fail)) {
    sel <- which(fail)
    warning("Parsing failed for ", 
      paste0("'", x[utils::head(sel, 5)], "'", collapse = ", "),
      if (length(sel) > 5) ", ..." else ".")
  }
  # Convert to Date first convert to number of days since 1600 and 
  # convert that to number of days since 1970. The reason to choose
  # 1600 is that the Gregorian calencer repeats every 400 years (we 
  # could also have choosen 0 or 400, or 2000 etc.
  y <- res$year - 1600
  ndays <- y * 365 +
    (y-1) %/% 4 -
    (y-1) %/% 100 + 
    (y-1) %/% 400 
  ndays <- ndays - 135139
  ndays <- ndays + res$yearday - 1L
  as.Date(ndays)
}

