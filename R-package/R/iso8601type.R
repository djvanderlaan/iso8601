

#' Determine the type of ISO8601 strings
#'
#' @param x character vector with ISO8601 strings
#'
#' @return
#' Character vector with the same length as `x` indicating the type of object
#' each element in `x` is. Elements of this string are:
#'
#' \item{Y}{Year.}
#' \item{M}{Month, or minutes in the time part. When followed by a '.' in the
#' time part these are fractional minutes.}
#' \item{D}{Day, this can be dau of the month, day of the week or day of the year.}
#' \item{T}{Marks the start of the time part.}
#' \item{H}{Hour. When followed by a '.' these are fractional hours.}
#' \item{M}{Month.}
#' \item{S}{Seconds. When followed by a '.' these are fractional seconds.}
#' \item{Z}{Time is in GMT/Zulu time.}
#' \item{±Z}{The time zone is indicated using an offset from GMT.}
#' \item{P}{A period. These are not parsed further.}
#' \item{I}{An interval. These are not parsed further.}
#' \item{R}{A repeating interval. These are not parsed further.}
#'
#' @examples
#' iso8601type(c("T12", "2045-W05-1T13.5", "2012-12-05", "13:25"))
#'
#' @export
iso8601type <- function(x) {
  res <- rcpp_type(x)
  tz <- factor(res %% 10, levels = c(0, 1, 2), labels = c("", "Z", "\u00B1Z"))
  t <- factor((res %/% 10) %% 10, levels = c(0, 1, 2, 3, 4, 5, 6), 
    labels = c("", "TH.", "TH", "THM.", "THM", "THMS.", "THMS"))
  d <- factor(((res %/% 10) %/% 10) %% 10, levels = c(0, 1, 2, 3, 4, 5, 6),
    labels = c("", "Y", "YM", "YMD", "YW", "YWD", "YD"))
  o <- factor(res %/% 1000, levels = c(0, 1, 2, 3), labels = c("", "P", "I", "R"))
  r <- paste0(o, d, t, tz)
  r[is.na(res)] <- NA
  r
}

