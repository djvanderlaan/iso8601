
#' Split Date, Time and DateTime ISO8601 strings into their elements
#'
#' @param x character vector of date, time or date-time strings
#'
#' @param transformdate Transform the date to the given format. This also
#' immplies that missing parts of the date are replaces by values of 1.
#'
#' @param ndigitsyear Number of digits used to encode the year. This should be
#' an integer with values >= 4 with the same length as \code{x} or length one.
#' When it is a vector with length greater than one, a different value is used
#' for each element of \code{x}.
#'
#' @return 
#' Returns a \code{data.frame} with possibly the following columns:
#'
#' \item{type}{Type of ISO 8601 string. A factor with the following possible
#' values: 'Date', 'Time', 'Datetime', 'Duration', 'Interval',
#' 'RepeatingInterval'.}
#' \item{year}{Year.}
#' \item{month}{Month.}
#' \item{day}{Day of the month.}
#' \item{week}{Week}
#' \item{weekday}{Day of the week}
#' \item{yearday}{Day of the year.}
#' \item{hour}{Hour of the day.}
#' \item{minutes}{Minutes}
#' \item{seconds}{Seconds}
#' \item{tzoffsethours}{The time zone offset. An offset of +1 means 1 hour to
#' the east of GMT.}
#' \item{tzoffsetminutes}{The additional offset in minutes (between 0 and 59).}
#'
#' Columns corresponding to elements that do not occur in any of the strings are
#' omitted from the resulting \code{data.frame}.
#'
#' @examples
#' iso8601todataframe(c("2014-W01-1", "2041-02-12T12+00", NA, "T22"))
#'
#' iso8601todataframe(c("2014-W01-1", "2041-02-12T12+00", NA, "T22"),
#'   transformdate = "toyearmonthday")
#'
#' @useDynLib iso8601
#' @import Rcpp
#' @importFrom Rcpp evalCpp
#' @export
iso8601todataframe <- function(x, 
    transformdate = c("no", "toyearmonthday", "toyearday"),
    ndigitsyear = 4L) {
  transformdate <- match.arg(transformdate)
  transformdate <- match(transformdate, 
    c("no", "toyearmonthday", "toyearday")) - 1L
  ndigitsyear <- as.integer(ndigitsyear)
  stopifnot(!anyNA(ndigitsyear))
  stopifnot(length(ndigitsyear) == 1 || length(ndigitsyear) == length(x))
  stopifnot(all(ndigitsyear >= 4))
  extrayearlen <- rep(ndigitsyear - 4, length.out = length(x))
  res <- rcpp_parse_iso_dateframe(x, transformdate, extrayearlen)
  res$type <- factor(res$type, levels = 1:6, labels = c("Date", "Time", 
      "Datetime", "Duration", "Interval", "RepeatingInterval"))
  sel <- sapply(res, \(x) length(x) != 0)
  # Keep type
  sel[1] <- TRUE 
  res <- res[sel]
  structure(res, row.names = seq_len(length(x)), class = "data.frame")
}
