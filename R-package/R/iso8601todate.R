#' Convert date in ISO8601 format into R Date object
#'
#' @param x character vector of ISO8601 date string. When the string also
#' contains a time part, this is ignored.
#'
#' @param ndigitsyear Number of digits used to encode the year. This should be
#' an integer with values >= 4 with the same length as \code{x} or length one.
#' When it is a vector with length greater than one, a different value is used
#' for each element of \code{x}.
#'
#' @details
#' Dates are accepted in any of the formats supported by ISO8601.
#'
#' @return
#' Returns a \code{\link{Date}} object with the same length as \code{x}. 
#'
#' @examples
#' iso8601todate(c("2024-01-01", "2024-W01-1", "2024001", 
#'   "2024-01-01T12:30"))
#' 
#' iso8601todate("2019-08-17")
#' iso8601todate("2019-08")
#' iso8601todate("2019")
#' iso8601todate("20190817")
#' iso8601todate("2019-W33-6")
#' iso8601todate("2019-W33")
#' iso8601todate("2019W336")
#' iso8601todate("2019W33")
#' iso8601todate("2019-229")
#' iso8601todate("2019229")
#' iso8601todate("\u22120009-123")
#' iso8601todate("-0009")
#' iso8601todate("+002019-229", ndigitsyear = 6)
#'
#' @useDynLib iso8601
#' @import Rcpp
#' @importFrom Rcpp evalCpp
#' @export
iso8601todate <- function(x, ndigitsyear = 4L) {
  res <- iso8601todataframe(x, "toyearday", ndigitsyear)
  # Handle errors
  d  <- res$type == "Date" & !is.na(res$type)
  dt <- res$type == "Datetime" & !is.na(res$type)
  ok <- d | dt | is.na(res$type)
  if (any(!ok)) {
    sel <- which(!ok)
    warning("No all string contain dates. Returning NA for ",
      paste0("'", x[utils::head(sel, 5)], "'", collapse = ", "),
      if (length(sel) > 5) ", ..." else ".")

  }
  if (!utils::hasName(res, "year")) 
    res$year <- rep(NA_integer_, length(x))
  if (!utils::hasName(res, "yearday")) 
    res$yearday <- rep(NA_integer_, length(x))
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

