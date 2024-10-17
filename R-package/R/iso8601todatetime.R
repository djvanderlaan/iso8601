
#' Convert date-time in ISO8601 format into R POSIXct object
#'
#' @param x character vector of date-time objects
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
#' @useDynLib iso8601
#' @import Rcpp
#' @importFrom Rcpp evalCpp
#' @export
iso8601todatetime <- function(x) {
  res <- rcpp_parse_datetime(x)
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
  res$isdst <- rep(0L, n)
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

