library(iso8601)
source("helpers.R")



x <- c("12:40:50", "T12", "T231312.12", NA)
t1 <- iso8601totime(x)
t2 <- as.POSIXct(c("1970-01-01 12:40:50", "1970-01-01 12:00:00", 
    "1970-01-01 23:13:12.12", NA), tz = "GMT")
expect_equal(t1, t2, attributes = FALSE)
expect_equal(class(t1), c("Time", "POSIXct", "POSIXt"))
expect_equal(attr(t1, "tzone"), "GMT")

expect_warning(x <- iso8601totime("foo"))
expect_equal(x, as.POSIXct(NA, tz = "GMT"), attributes = FALSE)

x <- iso8601totime(character(0))
expect_equal(x, as.POSIXct(character(0), tz = "GMT"), attributes = FALSE)
expect_equal(class(x), c("Time", "POSIXct", "POSIXt"))
expect_equal(attr(x, "tzone"), "GMT")


