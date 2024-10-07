

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
  local <- all(res$zone == "")
  gmt <- all(res$zone != "")
  tzone <- if (local) "" else if (gmt) "GMT" else ""
  if (gmt) res$zone <- "GMT"
  structure(res, tzone = "", class = c("POSIXlt", "POSIXT"))
}


#res <- parsedatetime(c("2024-01-01T12:30", "2024-01-01T12:30"))
#res
#unclass(res)

#
#
#local <- all(res$zone == "")
#local
#
#gmt <- all(res$zone != "")
#gmt
#
#unique(res$zone)
#
