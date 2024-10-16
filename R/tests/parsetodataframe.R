
library(iso8601)

source("helpers.R")

x <- parsetodataframe(c("2024-W01-6", "2041-02-12T12+05:20", NA, "T22"))
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

expect_warning(x <- parsetodataframe("FOO"))
expect_equal(x$type, factor(c(NA), levels = 1:6, 
  labels = c("Date", "Time", "Datetime", "Duration", 
    "Interval", "RepeatingInterval")))
expect_equal(names(x), c("type"))


x <- parsetodataframe(character(0))
expect_equal(names(x), c("type"))
expect_equal(nrow(x), 0)


# Transformdate
x <- parsetodataframe("2024-001", "tomonthyearday")
expect_equal(names(x), c("type", "year", "month", "day"))
expect_equal(x$year, 2024L)
expect_equal(x$month, 1)
expect_equal(x$day, 1)

x <- parsetodataframe("2024-02-05", "toyearday")
expect_equal(names(x), c("type", "year", "yearday"))
expect_equal(x$year, 2024L)
expect_equal(x$yearday, 36)

x <- parsetodataframe("2024", "toyearday")
expect_equal(names(x), c("type", "year", "yearday"))
expect_equal(x$year, 2024L)
expect_equal(x$yearday, 1)

x <- parsetodataframe(NA_character_, "toyearday")
expect_equal(names(x), c("type"))

