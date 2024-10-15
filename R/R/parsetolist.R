# Parse ISO8601 strings into a list structure
#
# @param x vector of IS08601 strings
#
# @details
# The functions \code{\link{parsedate}}, \code{\link{parsetime}} and
# \code{\link{parsedatetime}} parse ISO8601 strings into the most appropriate
# R-types. In this conversion some information is lost. For example, when
# converting a date '2024-01' to 'Date', the date is converted to '2024-01-01'
# as 'Date' object cannot represent partial dates. The current function does
# leave all information in the original string intact. However, at the code of
# more complex result. For example parsing the previous string would result in
# an object `list( list(year = 2024L, month = 1L) )` (the class attribute has
# been omitted in this example). 
#
# @return
# Returns an unnamed list with the same length as \code{x}. Each element
# contains the parsed corresponding element from \code{x}. In case the string
# could not be parsed or when the element of \code{x} was \code{NA}, the
# element contains \code{NA}. For elements that could be parsed, the list
# contains a list containing the elements of the string.
#
# The elements have a class assigned: 'ISO8601Time' for a time, 'ISO8601Date'
# for a date and 'ISO8601DateTime' for a date time. The list containing the
# results has a type 'ISO8601' that is used for pretty printing the result. It
# is possible to insert the 'ISO8601' object into a \code{data.frame}.
#
# For dates and date-times the elements can contain the following properties:
# \item{year}{Year.}
# \item{month}{Month.}
# \item{day}{Day of the month.}
# \item{week}{Week}
# \item{weekday}{Day of the week}
# \item{yearday}{Day of the year.}
# 
# For times and date-times the elements can contain the following properties:
# \item{hour}{Hour of the day.}
# \item{minutes}{Minutes}
# \item{seconds}{Seconds}
# \item{tz_offset_hours}{The time zone offset. An offset of +1 means 1 hour to
# the east of GMT.}
# \item{tz_offset_minutes}{The additional offset in minutes (between 0 and 59).
# The object always contains both 'tz_offset_minutes' and 'tz_offset_hours'.
# When both are missing, time is in local time.}
#
# @examples
# x <- parsetolist(c("2024-W01-1", "2041-02-12T12+00:00", NA, "T22"))
# x
# x[[1]]
# x[[2]]
# x[[4]]
# x[1:2]
# y <- data.frame(iso = x)
#
# 
# @useDynLib iso8601
# @import Rcpp
# @importFrom Rcpp evalCpp
parsetolist <- function(x) {
  res <- rcpp_parse_iso_list(x)
  structure(res, class = "ISO8601")
}

# @export
format.ISO8601 <- function(x, ...) {
  sapply(x, format)
}

# @export
format.ISO8601Date <- function(x, ...) {
  paste0(
    sprintf("%04d", x$year),
    sprintf("-%02d", x$month),
    sprintf("-%02d", x$day),
    sprintf("-W%02d", x$week),
    sprintf("-%01d", x$weekday),
    sprintf("-%03d", x$yearday)
  )
}

# @export
format.ISO8601TimeZone <- function(x, ...) {
  if (utils::hasName(x, "tz_offset_hours")) {
    if (x$tz_offset_hours == 0 && x$tz_offset_minutes == 0) {
      "Z"
    } else {
      sign <- if (x$tz_offset_hours > 0) "+" else "-"
      print(sign)
      sprintf("%s%02d:%02d", sign, abs(x$tz_offset_hours), x$tz_offset_minutes)
    }
  } else {
    ""
  }
}

# @export
format.ISO8601Time <- function(x, ...) {
  paste0(
    sprintf("T%02d", x$hour),
    sprintf(":%02d", x$minutes),
    sprintf(":%02d", x$seconds),
    format.ISO8601TimeZone(x)
  )
}

# @export
format.ISO8601DateTime <- function(x, ...) {
  paste0(format.ISO8601Date(x), format.ISO8601Time(x))
}


# @export
print.ISO8601 <- function(x, ...) {
  print(format(x))
}

# @export
as.data.frame.ISO8601 <- function(x, row.names = NULL, optional = FALSE, ..., nm = deparse1(substitute(x))) {
  force(nm)
  nrows <- length(x)
  if (is.null(row.names) && nrows == 0) {
    row.names = character(0)
  } else if (is.null(row.names) && !is.null(names(x))) {
    row.names = names(x)
  } else if (is.null(row.names)) {
    row.names = seq_len(nrows)
  }
  stopifnot(is.character(row.names) || is.integer(row.names))
  stopifnot(length(row.names) == nrows)
  if (!is.null(names(x))) names(x) <- NULL
  res <- list(x)
  if (!optional) names(res) <- nm
  structure(res, row.names = row.names, class = "data.frame")
}

# @export
`[.ISO8601` <- function(x, ..., drop = TRUE) {
  structure(NextMethod("["), class=  oldClass(x))
}

