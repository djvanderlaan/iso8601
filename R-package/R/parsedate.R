#' Convert date in ISO8601 format into R Date object
#'
#' @param x character vector of ISO8601 date string. When the string also
#' contains a time part, this is ignored.
#'
#' @details
#' Dates are accepted in any of the formats supported by ISO8601.
#'
#' @return
#' Returns a \code{\link{Date}} object with the same length as \code{x}. 
#'
#' @examples
#' parsedate(c("2024-01-01", "2024-W01-1", "2024001", 
#'   "2024-01-01T12:30"))
#'
#' @useDynLib iso8601
#' @import Rcpp
#' @importFrom Rcpp evalCpp
#' @export
parsedate <- function(x) {
  res <- parsetodataframe(x, "toyearday")
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

#parsedate <- function(x) {
#  res <- rcpp_parse_date(x)
#  fail <- is.na(res$year) & !is.na(x)
#  if (any(fail)) {
#    sel <- which(fail)
#    warning("Parsing failed for ", 
#      paste0("'", x[utils::head(sel, 5)], "'", collapse = ", "),
#      if (length(sel) > 5) ", ..." else ".")
#  }
#  # Convert to Date first convert to number of days since 1600 and 
#  # convert that to number of days since 1970. The reason to choose
#  # 1600 is that the Gregorian calencer repeats every 400 years (we 
#  # could also have choosen 0 or 400, or 2000 etc.
#  y <- res$year - 1600
#  ndays <- y * 365 +
#    (y-1) %/% 4 -
#    (y-1) %/% 100 + 
#    (y-1) %/% 400 
#  ndays <- ndays - 135139
#  ndays <- ndays + res$yearday - 1L
#  as.Date(ndays)
#}

