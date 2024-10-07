

parsedatetime <- function(x) {
  res <- rcpp_parse_datetime(x)
  n <- length(x)
  res$year <- res$year - 1900L
  res$wday <- rep(NA_integer_, n)
  res$yday <- rep(NA_integer_, n)
  res$isdst <- rep(0L, n)
  res$gmtoff <- ifelse(res$zone == "Z", 0L, NA_integer_) 
  res <- res[c("sec", "min", "hour", "mday", "mon", "year", "wday", "yday", 
    "isdst", "zone", "gmtoff")]
  structure(res, tzone = "", class = c("POSIXlt", "POSIXT"))
}
