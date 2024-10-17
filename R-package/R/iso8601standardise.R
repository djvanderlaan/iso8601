#' Standardise ISO8601 strings
#'
#' @param x a character vector with valid ISO8601 date. time, or date-time
#' strings. 
#' 
#' @param fillmissing recplace missing parts ot dates, and times with the
#' minimum possible values. In dates this is 1, in times this is 0.
#'
#' @param toymd convert dates in year-week-weekday format, or year-day format to
#' year-month-day format.
#'
#' @param tozulu convert times to GMT. Note that this implies \code{fillmissing
#' = TRUE} for date-time strings with time zone.
#'
#' @return
#' Returns a character vector with the same length as \code{x} with the
#' ISO8601 strings in a standardised format. For input strings that are not a
#' valid ISO8601 time, date or date-time string \code{NA} is returned and a
#' warning is issued.
#'
#' @examples''
#' x <- c("2024-01-01T12:34", "2024W011", "2024-123T13:00:00+01", "T1530", NA)
#'
#' iso8601standardise(x)
#' iso8601standardise(x, fillmissing = FALSE)
#' iso8601standardise(x, toymd = FALSE)
#' iso8601standardise(x, tozulu = FALSE)
#'
#' @export
iso8601standardise <- function(x, fillmissing = TRUE, toymd = TRUE, 
    tozulu = TRUE) {
  stopifnot(is.logical(fillmissing) && length(fillmissing) == 1)
  stopifnot(is.logical(toymd) && length(toymd) == 1)
  stopifnot(is.logical(tozulu) && length(tozulu) == 1)
  rcpp_standardise(x, fillmissing = fillmissing, toymd = toymd, 
    to_zulu = tozulu)
}

