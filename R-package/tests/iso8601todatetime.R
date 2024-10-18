library(iso8601)

source("helpers.R")

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


# Next date gave issues in earlier version has to do with summer-winter-time
# crossing in CET/CEST
x <- "1999-10-25 03:14:06"
y <- iso8601todatetime(x)
z <- as.POSIXct(x)
expect_equal(y, z, attributes = FALSE)

