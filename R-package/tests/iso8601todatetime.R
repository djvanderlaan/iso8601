library(iso8601)

source("helpers.R")

# Note that testing of the parsing of all of the various date formats allowed in
# ISO8601 is done in the c++ library. We will not test these here. Here we will
# only test if the R-routines correctly call the c++ routines and that the
# result of those calls is handles correctly in R.

oldtz = Sys.getenv("TZ")
Sys.setenv(TZ="Etc/GMT+1")

x <- iso8601todatetime(c("2024-01-01T12:30", "2024-W01-1T12:30Z",
  "2024-001T12:30+01", NA))
expect_equal(x[1], as.POSIXct("2024-01-01 12:30"))
expect_equal(x[2], as.POSIXct("2024-01-01 12:30", tz = "GMT"), 
  attributes = FALSE)
expect_equal(x[3], as.POSIXct("2024-01-01 11:30", tz = "GMT"), 
  attributes = FALSE)
expect_equal(x[4], as.POSIXct(NA_character_, tz = ""), 
  attributes = FALSE)
expect_equal(attr(x, "tzone"), attr(as.POSIXct(0), "tzone"))
expect_equal(attr(x, "timezone"), c("", "GMT", "+01:00", NA))

x <- iso8601todatetime(c("2024-01-01T12:30Z", "2024-001T12:30Z"))
expect_equal(x, as.POSIXct(c("2024-01-01 12:30", "2024-01-01 12:30"),
  tz = "GMT"), attributes = FALSE)
expect_equal(attr(x, "tzone"), "GMT")
expect_equal(attr(x, "timezone"), c("GMT", "GMT"))

x <- iso8601todatetime(character(0))
expect_equal(x, 
  structure(as.POSIXct(numeric(0), tz="GMT"), timezone = character(0)))

x <- iso8601todatetime(NA_character_)
expect_equal(x[4], as.POSIXct(NA_character_, tz = ""), 
  attributes = FALSE)
expect_equal(attr(x, "tzone"), attr(as.POSIXct(0), "tzone"))
expect_equal(attr(x, "timezone"), c(NA_character_))

expect_warning(x <- iso8601todatetime("foo"))
expect_equal(x[4], as.POSIXct(NA_character_, tz = ""), 
  attributes = FALSE)
expect_equal(attr(x, "tzone"), attr(as.POSIXct(0), "tzone"))
expect_equal(attr(x, "timezone"), c(NA_character_))

# Different number of digits in year
x <- iso8601todatetime(c("2024-01-01T12:30", "2024-W01-1T12:30Z",
  "2024-001T12:30+01", NA))
expect_equal(x[1], as.POSIXct("2024-01-01 12:30"))
expect_warning(r <- iso8601todatetime("02024-01-01T12:30"))
expect_equal(r, as.POSIXct(NA_character_), attributes = FALSE)
r <- iso8601todatetime("+02024-01-01T12:30", ndigitsyear=5)
expect_equal(r, as.POSIXct("2024-01-01 12:30"), attributes = FALSE)
expect_warning(r <- iso8601todatetime("2024-01-01T12:30", ndigitsyear = 5))
expect_equal(r, as.POSIXct(NA_character_), attributes = FALSE)
expect_error(r <- iso8601todatetime("2024-01-01T12:30", ndigitsyear = 3))
expect_error(r <- iso8601todatetime("2024-01-01T12:30", ndigitsyear = NA))
r <- iso8601todatetime(c("+02024-01-01T12:30", "2024-01-01T12:30"), ndigitsyear = c(5,4))
expect_equal(r, rep(as.POSIXct("2024-01-01 12:30"),2), attributes = FALSE)


# Next date gave issues in earlier version has to do with summer-winter-time
# crossing in CET/CEST
x <- "1999-10-25 03:14:06"
y <- iso8601todatetime(x)
z <- as.POSIXct(x)
expect_equal(y, z, attributes = FALSE)


# =====================================================================
# === DATE-TIME VARIANTS
# =====================================================================

check_datetime <- function(x, d, tz = "", ...) {
  r <- iso8601todatetime(x, ...)
  if (!methods::is(d, "POSIXct")) d <- as.POSIXct(d, tz = tz)
  expect_equal(r, d, attributes = FALSE)
}

check_datetime("2022-12-22T12:23:34", "2022-12-22 12:23:34")
check_datetime("2022-W12-3 12:23.5", "2022-03-23 12:23:30")
check_datetime("2022-123T12Z", "2022-05-03 12:00:00", tz = "GMT")
check_datetime("+002022-12-22T12:23:34Z", "2022-12-22 12:23:34", 
  tz = "GMT", ndigitsyear = 6)

expect_warning(iso8601todatetime("2021-12T14:23:23"))
expect_warning(iso8601todatetime(" 2021-12-23T14:23:23"))
expect_warning(iso8601todatetime("2021-12-23T14:23:23 "))
expect_warning(iso8601todatetime("2021-12-23T14:23:23/2021-12-23T14:25:00"))
expect_warning(iso8601todatetime("2021-12-23"))
expect_warning(iso8601todatetime("2021-12-23/2021-12-25"))
expect_warning(iso8601todatetime("2021-12-23/2021-12-25"))
expect_warning(iso8601todatetime("002022-12-22T12:23:34", ndigitsyear=6))
expect_warning(iso8601todatetime("+002022-12-22T12:23:34", ndigitsyear=5))


Sys.setenv(TZ = oldtz)
