library(iso8601)
source("helpers.R")

check_date <- function(x, d) {
  r <- iso8601todate(x)
  if (!methods::is(d, "Date")) d <- as.Date(d)
  expect_equal(r, d)
}

# YYYY-MM-DD
check_date("2022", "2022-01-01")
# There are 146097 days in 400 years
check_date("-0378", as.Date("2022-01-01") - 6*146097)
check_date("\u22120378", as.Date("2022-01-01") - 6*146097)
check_date("+2022", "2022-01-01")
check_date("2022-12-22", "2022-12-22")
check_date("20221222", "2022-12-22")
check_date("2022-12", "2022-12-01")
check_date("-03781222", as.Date("2022-12-22") - 6*146097)

# INVALID YYYY-MM-DD
expect_warning(iso8601todate("202212"))
expect_warning(iso8601todate("2022-1222"))
expect_warning(iso8601todate("202212-22"))
expect_warning(iso8601todate("2022-13-22"))
expect_warning(iso8601todate("2022-00-22"))
expect_warning(iso8601todate("2022-12-32"))
expect_warning(iso8601todate("2022-12-00"))
expect_warning(iso8601todate("2022-12-1"))
expect_warning(iso8601todate("222-12-32"))
expect_warning(iso8601todate("2022-12-"))
expect_warning(iso8601todate("2022-12-01 "))
expect_warning(iso8601todate(" 2022-12-01"))
expect_warning(iso8601todate("2022-12 "))


