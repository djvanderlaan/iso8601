
library(iso8601)

source("helpers.R")

# Note that testing of the parsing of all of the various date formats allowed in
# ISO8601 is done in the c++ library. We will not test these here. Here we will
# only test if the R-routines correctly call the c++ routines and that the
# result of those calls is handles correctly in R.

x <- iso8601todataframe(c("2024-W01-6", "2041-02-12T12+05:20", NA, "T22"))
expect_equal(x$type, factor(c(1,3,NA,2), levels = 1:6, 
  labels = c("Date", "Time", "Datetime", "Duration", 
    "Interval", "RepeatingInterval")))
expect_equal(x$year, c(2024L, 2041L, NA, NA))
expect_equal(x$month, c(NA, 2L, NA, NA))
expect_equal(x$day, c(NA, 12L, NA, NA))
expect_equal(x$week, c(1L, NA, NA, NA))
expect_equal(x$weekday, c(6L, NA, NA, NA))
expect_equal(x$hour, c(NA, 12, NA, 22))
expect_equal(x$tzoffsethours, c(NA, 5, NA, NA))
expect_equal(x$tzoffsetminutes, c(NA, 20, NA, NA))
expect_equal(names(x), c("type", "year", "month", "day", "week", 
    "weekday", "hour", "tzoffsethours", "tzoffsetminutes"))

expect_warning(x <- iso8601todataframe("FOO"))
expect_equal(x$type, factor(c(NA), levels = 1:6, 
  labels = c("Date", "Time", "Datetime", "Duration", 
    "Interval", "RepeatingInterval")))
expect_equal(names(x), c("type"))


x <- iso8601todataframe(character(0))
expect_equal(names(x), c("type"))
expect_equal(nrow(x), 0)


# Transformdate
x <- iso8601todataframe("2024-001", "toyearmonthday")
expect_equal(names(x), c("type", "year", "month", "day"))
expect_equal(x$year, 2024L)
expect_equal(x$month, 1)
expect_equal(x$day, 1)

x <- iso8601todataframe("2024-02-05", "toyearday")
expect_equal(names(x), c("type", "year", "yearday"))
expect_equal(x$year, 2024L)
expect_equal(x$yearday, 36)

x <- iso8601todataframe("2024", "toyearday")
expect_equal(names(x), c("type", "year", "yearday"))
expect_equal(x$year, 2024L)
expect_equal(x$yearday, 1)

x <- iso8601todataframe(NA_character_, "toyearday")
expect_equal(names(x), c("type"))


# Failed in earlier version
# tranformdate did not work for datetime
x <- iso8601todataframe("2019-08-17T16:15:14+00", "toyearday")
expect_equal(x$year, 2019L)
expect_equal(x$month, NULL)
expect_equal(x$day, NULL)
expect_equal(x$yearday, 229L)
expect_equal(x$hour, 16)
expect_equal(x$minutes, 15)
expect_equal(x$seconds, 14)
expect_equal(x$tzoffsethours, 0)
expect_equal(x$tzoffsetminutes, 0)

# Failed in earlier version
# tranformdate did not work for datetime
x <- iso8601todataframe("2019229T161514", "toyearmonthday")
expect_equal(x$year, 2019L)
expect_equal(x$month, 8L)
expect_equal(x$day, 17L)
expect_equal(x$yearday, NULL)
expect_equal(x$hour, 16)
expect_equal(x$minutes, 15)
expect_equal(x$seconds, 14)
expect_equal(x$tzoffsethours, NULL)
expect_equal(x$tzoffsetminutes, NULL)

