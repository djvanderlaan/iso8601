#library(iso8601)
#
#source("helpers.R")
#
#x <- parsetolist(c("2024-W01-1", "2041-02-12T12+00:00", NA, "T22"))
#
#expect_equal(x[[1]], 
#  structure(list(year = 2024L, week = 1L, weekday=1L), class="ISO8601Date")
#)
#
#expect_equal(x[[2]], 
#  structure(list(year = 2041L, month = 2L, day=12L, hour = 12, 
#      tz_offset_hours = 0L, tz_offset_minutes = 0L), class="ISO8601DateTime")
#)
#
#expect_equal(x[[3]], NA_integer_)
#
#expect_equal(x[[4]], 
#  structure(list(hour = 22), class="ISO8601Time")
#)
#
#expect_warning(x <- parsetolist("FOO"))
#expect_equal(x[[1]], NA_integer_)


