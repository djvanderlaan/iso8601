library(iso8601)
source("helpers.R")

# Note that testing of the parsing of all of the various date formats allowed in
# ISO8601 is done in the c++ library. We will not test these here. Here we will
# only test if the R-routines correctly call the c++ routines and that the
# result of those calls is handles correctly in R.

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


