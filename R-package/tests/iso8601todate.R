library(iso8601)
source("helpers.R")

x <- c("2024-01-01", "2019-03-14", NA, "1900-12-12", "2000-03-01", 
  "2000-02-29")
expect_equal(iso8601todate(x), as.Date(x))

expect_warning(x <- iso8601todate("foo"))
expect_equal(x, as.Date(NA))

x <- iso8601todate(character(0))
expect_equal(x, as.Date(integer(0)))

expect_equal(iso8601todate("2024"), as.Date("2024-01-01"))
expect_equal(iso8601todate("2024-01"), as.Date("2024-01-01"))
expect_equal(iso8601todate("2024-W01"), as.Date("2024-01-01"))

# Different number of digits in year
expect_warning(r <- iso8601todate("02024-01-01"))
expect_equal(r, as.Date(NA_character_))
r <- iso8601todate("+02024-01-01", ndigitsyear=5)
expect_equal(r, as.Date("2024-01-01"))
expect_warning(r <- iso8601todate("2024-01-01", ndigitsyear = 5))
expect_equal(r, as.Date(NA_character_))
expect_error(r <- iso8601todate("2024-01-01", ndigitsyear = 3))
expect_error(r <- iso8601todate("2024-01-01", ndigitsyear = NA))
r <- iso8601todate(c("+02024-01-01", "2024-01-01"), ndigitsyear=c(5,4))
expect_equal(r, as.Date(c("2024-01-01", "2024-01-01")))


# =====================================================================
# === DATE VARIANTS
# =====================================================================

check_date <- function(x, d, ...) {
  r <- iso8601todate(x, ...)
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

# YYYY-DDD
check_date("2022-123", "2022-05-03")
check_date("-0378-123", as.Date("2022-05-03") - 6*146097)
check_date("2022123", "2022-05-03")
check_date("2024-366", "2024-12-31")

# INVALID YYYY-DDD
expect_warning(iso8601todate("2022-000"))
expect_warning(iso8601todate("2022-366"))
expect_warning(iso8601todate("2022-367"))
expect_warning(iso8601todate("2022-123-"))
expect_warning(iso8601todate("2022-123 "))

# YYYY-WW-D
check_date(iso8601todate("2022-W12-3"), "2022-03-23")
check_date(iso8601todate("2022W123"), "2022-03-23")
check_date(iso8601todate("2022-W12"), "2022-03-21")
check_date(iso8601todate("2022W12"), "2022-03-21")

# INVALID YYYY-WW-D
expect_warning(iso8601todate("2022-W123"))
expect_warning(iso8601todate("2022-W54-3"))
expect_warning(iso8601todate("2022-W00-3"))
expect_warning(iso8601todate("2022-W12-0"))
expect_warning(iso8601todate("2022-W12-8"))
expect_warning(iso8601todate("2022-W12-"))

# YYYYYY
check_date("+002022-12-22", "2022-12-22", ndigitsyear = 6)
check_date("-000378-12-22", as.Date("2022-12-22") - 6*146097, ndigitsyear = 6)
check_date("\u2212000378-12-22", as.Date("2022-12-22") - 6*146097, ndigitsyear = 6)

# INVALID YYYYYY
expect_warning(iso8601todate("+002022-12-22", ndigits = 5))
expect_warning(iso8601todate("+002022-12-22", ndigits = 7))
expect_warning(iso8601todate("002022-12-22", ndigits = 6))

