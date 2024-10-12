#' Convert time in ISO8601 format into R POSIXct object
#'
#' @param x character vector of time strings
#'
#' @details
#' Times are acceptes in any of the formats supported by ISO8601.
#'
#' @return
#' Returns a \code{Time} object, which is a subclass of \code{\link{POSIXct}}
#' object.  Time is represented as a time on 1970-01-01. The only difference
#' between the \code{Time} object and the \code{POSIXct} object is the
#' formatting, which leaves out the date part.
#'
#' @examples
#' parsetime(c("12:30:12", "T12", "T000910"))
#'
#' @useDynLib iso8601
#' @import Rcpp
#' @importFrom Rcpp evalCpp
#' @export
parsetime <- function(x) {
  res <- rcpp_parse_time(x)
  fail <- is.na(res) & !is.na(x)
  if (any(fail)) {
    sel <- which(fail)
    warning("Parsing failed for ", 
      paste0("'", x[utils::head(sel, 5)], "'", collapse = ", "),
      if (length(sel) > 5) ", ..." else ".")
  }
  # rcpp_parse_date returns the number of seconds from 00:00:00. Convert to
  # POSIXct; this means we get a time on 1970-01-01. 
  res <- as.POSIXct(res, tz = "GMT")
  structure(res, class = c("Time", "POSIXct", "POSIXt"), tzone = "GMT")
}


#'@export
print.Time <- function(x, ...) {
  if (length(x)) {
    print(format(x), ...)
  } else {
    cat(class(x)[1], "of length 0\n")
  }
}

#'@export
format.Time <- function(x, format = "T%H:%M:%OS", ...) {
  NextMethod("format", x, format = format, tz = "GMT")
}

