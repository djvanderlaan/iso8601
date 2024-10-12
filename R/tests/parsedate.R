library(iso8601)
source("helpers.R")


x <- c("2024-01-01", "2019-03-14", NA, "1900-12-12", "2000-03-01", 
  "2000-02-29")
expect_equal(parsedate(x), as.Date(x))

expect_warning(x <- parsedate("foo"))
expect_equal(x, as.Date(NA))

x <- parsedate(character(0))
expect_equal(x, as.Date(integer(0)))

expect_equal(parsedate("2024"), as.Date("2024-01-01"))
expect_equal(parsedate("2024-01"), as.Date("2024-01-01"))
expect_equal(parsedate("2024-W01"), as.Date("2024-01-01"))


