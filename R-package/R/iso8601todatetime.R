
#' Convert date-time in ISO8601 format into R POSIXct object
#'
#' @param x character vector of date-time objects
#'
#' @param ndigitsyear Number of digits used to encode the year. This should be
#' an integer with values >= 4 with the same length as \code{x} or length one.
#' When it is a vector with length greater than one, a different value is used
#' for each element of \code{x}.
#'
#' @details
#' Date-time strings with a time-zone are converted to UTC.  If all date-time
#' strings have a time zone the returned object will have it's display time zone
#' set to GMT, otherwise the time zone is set to local time. It is assumed that
#' date-times without time zone are in local time.
#'
#' Missing parts of the time are set to 0. 
#'
#' @return
#' Returns a \code{\link{POSIXct}} object with the same length as \code{x}. The
#' object additionally has a 'timezone' attribute which is a character vector
#' with the same length as \code{x}. This vector contains the original time zone
#' of the ISO8601 date-time.
#'
#' @examples
#' x <- iso8601todatetime(c("2024-01-01T12:30", "2024-W01-1T12:30Z",
#'   "2024-001T12:30+01"))
#' x
#' attr(x, "timezone")
#'
#' # Examples of full date-times
#' iso8601todatetime("2019-08-17T16:15:14Z")
#' iso8601todatetime("2019-08-17T161514Z")
#' iso8601todatetime("2019-08-17T16:15Z")
#' iso8601todatetime("2019-08-17T1615")
#' iso8601todatetime("2019-08-17T16Z")
#' iso8601todatetime("+002019-08-17T16:15:14Z", ndigitsyear = 6)
#' 
#' # Fractional times
#' iso8601todatetime("2019-08-17T16:15:14,00Z")
#' iso8601todatetime("2019-08-17T16:15:14.00Z")
#' iso8601todatetime("2019-08-17T161514.00Z")
#' iso8601todatetime("2019-08-17T161514,00Z")
#' iso8601todatetime("2019-08-17T16:15.24Z")
#' iso8601todatetime("2019-08-17T16:15,24Z")
#' iso8601todatetime("2019-08-17T1615.24Z")
#' iso8601todatetime("2019-08-17T1615,24Z")
#' iso8601todatetime("2019-08-17T16.2539Z")
#' iso8601todatetime("2019-08-17T16,2539Z")
#' 
#' # When extended format T can be omitted
#' iso8601todatetime("2019-08-17 16:15:14Z")
#' iso8601todatetime("2019-08-17 16:15:14,00Z")
#' iso8601todatetime("2019-08-17 16:15:14.00Z")
#' iso8601todatetime("2019-08-17 16:15Z")
#' iso8601todatetime("2019-08-17 16:15Z")
#' iso8601todatetime("2019-08-17 16:15.24Z")
#' iso8601todatetime("2019-08-17 16:15,24Z")
#' 
#' # Time zones
#' iso8601todatetime("2019-08-17T16:15:14Z")
#' iso8601todatetime("2019-08-17T16:15:14+01:00")
#' iso8601todatetime("2019-08-17T16:15:14\u00b100:00")
#' iso8601todatetime("2019-08-17T16:15:14-01")
#' iso8601todatetime("2019-08-17T16:15:14\u221200:00")
#' iso8601todatetime("2019-08-17T16:15:14")
#'
#' @useDynLib iso8601
#' @import Rcpp
#' @importFrom Rcpp evalCpp
#' @export
iso8601todatetime <- function(x, ndigitsyear = 4L) {
  ndigitsyear <- as.integer(ndigitsyear)
  stopifnot(!anyNA(ndigitsyear))
  stopifnot(length(ndigitsyear) == 1 || length(ndigitsyear) == length(x))
  stopifnot(all(ndigitsyear >= 4))
  extrayearlen <- rep(ndigitsyear - 4, length.out = length(x))
  res <- rcpp_parse_datetime(x, TRUE, extrayearlen)
  fail <- is.na(res$year) & !is.na(x)
  if (any(fail)) {
    sel <- which(fail)
    warning("Parsing failed for ", 
      paste0("'", x[utils::head(sel, 5)], "'", collapse = ", "),
      if (length(sel) > 5) ", ..." else ".")
  }
  n <- length(x)
  res$mon <- res$mon - 1L
  res$year <- res$year - 1900L
  res$wday <- rep(NA_integer_, n)
  res$yday <- rep(NA_integer_, n)
  res$isdst <- rep(-1L, n)
  res$gmtoff <- ifelse(res$zone == "Z", 0L, NA_integer_) 
  res <- res[c("sec", "min", "hour", "mday", "mon", "year", "wday", 
    "yday", "isdst", "zone", "gmtoff")]
  local <- all(res$zone == "" & !is.na(res$zone))
  gmt <- all(res$zone != "" & !is.na(res$zone))
  tzone <- if (!gmt) "" else "GMT"
  # store original zones
  zoneorig <- res$zone
  zoneorig[zoneorig == "Z"] <- "GMT"
  res$zone[res$zone != ""] <- "GMT"
  res <- structure(res, tzone = tzone, class = c("POSIXlt", "POSIXT"))
  # Convert to POSIXct
  res <- lttoct(res)
  attr(res, "timezone") <- zoneorig
  res
}


lttoct <- function(x) {
  tzone <- attr(x, "tzone")[1]
  result <- rep(as.POSIXct(0, tz = tzone), length(x))
  zones <- unique(x$zone)
  for (zone in zones) {
    sel <- if (is.na(zone)) is.na(x$zone) else
      x$zone == zone & !is.na(x$zone)
    result[sel] <- as.POSIXct(x[sel], tz = zone)
  }
  result
}

