library(iso8601)
source("helpers.R")

x <- c("12:40:50", "T12", "121340", "T231312.12", NA)
t1 <- iso8601totime(x)
t2 <- as.POSIXct(c("1970-01-01 12:40:50", "1970-01-01 12:00:00", 
    "1970-01-01 12:13:40", "1970-01-01 23:13:12.12", NA), tz = "GMT")
expect_equal(t1, t2, attributes = FALSE)
expect_equal(class(t1), c("Time", "POSIXct", "POSIXt"))
expect_equal(attr(t1, "tzone"), "GMT")

expect_warning(x <- iso8601totime("foo"))
expect_equal(x, as.POSIXct(NA, tz = "GMT"), attributes = FALSE)

x <- iso8601totime(character(0))
expect_equal(x, as.POSIXct(character(0), tz = "GMT"), attributes = FALSE)
expect_equal(class(x), c("Time", "POSIXct", "POSIXt"))
expect_equal(attr(x, "tzone"), "GMT")

# =====================================================================
# === TIME VARIANTS
# =====================================================================

check_time <- function(x, d, tz = "", ...) {
  r <- iso8601totime(x, ...)
  if (!methods::is(d, "POSIXct")) d <- as.POSIXct(paste0("1970-01-01 ", d), tz = "GMT")
  expect_equal(r, d, attributes = FALSE)
}

check_time("T12:23:34", "12:23:34")
check_time("T122334", "12:23:34")
check_time("T12", "12:00:00")
check_time("T12.5", "12:30:00")
check_time("T12:23,5", "12:23:30")
check_time("T1223.5", "12:23:30")
check_time("T1223", "12:23:00")
check_time("T12:23:34.5", "12:23:34.5")
check_time("T122334,5", "12:23:34.5")
check_time("12:23:34", "12:23:34")
check_time("12:23", "12:23:00")
check_time("122334", "12:23:34")
check_time("12.5", "12:30:00")

expect_warning(iso8601totime("T") )
expect_warning(iso8601totime("T1") )
expect_warning(iso8601totime("T12:2334") )
expect_warning(iso8601totime("T1223:34") )
expect_warning(iso8601totime("T12:23.1:34") )
expect_warning(iso8601totime("T12:23:34.") )
expect_warning(iso8601totime("T12:23:34 ") )
expect_warning(iso8601totime(" T12:23:34 ") )
expect_warning(iso8601totime("T12:23:60") )
expect_warning(iso8601totime("T12:60:34") )
expect_warning(iso8601totime("T25:23:34") )
expect_warning(iso8601totime("T24:23:34") )
expect_warning(iso8601totime("1") )


