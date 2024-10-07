#' Standardise ISO8601 date-time strings
#'
#' @param x a character vector with valid ISO8601 date-time strins. 
#' 
#' @param fillmissing set missing minutes and seconds of the time part of the
#' string to 0.
#' 
#' @param toymd convert dates in year-week-weekday format, or year-day format to
#' year-month-day format.
#'
#' @param tozulu convert times to GMT.
#'
#' @return
#' Returns a character vector with the same length as \code{x} with the
#' date-time strings in a standardised format. For input strings that are not a
#' valid ISO8601 date-time string \code{NA} is returned.
#'
#' @examples
#' x <- c("2024-01-01T12:34", "2024W011T123400Z", "2024-123T13:00:00+01", NA)
#'
#' standardisedatetime(x)
#' standardisedatetime(x, fillmissing = FALSE)
#' standardisedatetime(x, toymd = FALSE)
#' standardisedatetime(x, tozulu = FALSE)
#'
#' @export
standardisedatetime <- function(x, fillmissing = TRUE, toymd = TRUE, tozulu = TRUE) {
  res <- rcpp_standardise_datetime(x, fillmissing = fillmissing, toymd = toymd, to_zulu = tozulu)
  if (any(is.na(res) & !is.na(x))) 
    warning("x contains invalid ISO8601 date-time strings. Returning NA for these strings.")
  res
}

