
#' @export
parsedatetime <- function(x) {
  res <- rcpp_parse_datetime(x)
  n <- length(x)
  res$year <- res$year - 1900L
  res$wday <- rep(NA_integer_, n)
  res$yday <- rep(NA_integer_, n)
  res$isdst <- rep(0L, n)
  res$gmtoff <- ifelse(res$zone == "Z", 0L, NA_integer_) 
  res <- res[c("sec", "min", "hour", "mday", "mon", "year", "wday", 
    "yday", "isdst", "zone", "gmtoff")]
  local <- all(res$zone == "")
  gmt <- all(res$zone != "")
  tzone <- if (local) "" else "GMT"
  res$zone[res$zone != ""] <- "GMT"
  if (!local && !gmt)
    warning("Mix of local time zone and GMT. Assuming GMT is local time.")
  structure(res, tzone = tzone, class = c("POSIXlt", "POSIXT"))
}


