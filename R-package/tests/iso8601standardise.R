library(iso8601)
source("helpers.R")

x <- c("2024-01-01T12:34", "2024W011", "2024-123T13:00:00+01", "T1530", NA)

expect_equal(iso8601standardise(x), 
  c("2024-01-01T12:34:00", "2024-01-01", "2024-05-02T12:00:00Z", 
    "T15:30:00", NA))
expect_equal(iso8601standardise(x, fillmissing = FALSE), 
  c("2024-01-01T12:34", "2024-01-01", "2024-05-02T12:00:00Z", 
    "T15:30", NA))
expect_equal(iso8601standardise(x, toymd = FALSE), 
  c("2024-01-01T12:34:00", "2024-W01-1", "2024-123T12:00:00Z", 
    "T15:30:00", NA))
expect_equal(iso8601standardise(x, tozulu = FALSE), 
  c("2024-01-01T12:34:00", "2024-01-01", "2024-05-02T13:00:00+01:00", 
    "T15:30:00", NA))
expect_equal(iso8601standardise(x, tozulu = FALSE, fillmissing = FALSE), 
  c("2024-01-01T12:34", "2024-01-01", "2024-05-02T13:00:00+01:00", 
    "T15:30", NA))
expect_equal(iso8601standardise(x, tozulu = FALSE, toymd = FALSE), 
  c("2024-01-01T12:34:00", "2024-W01-1", "2024-123T13:00:00+01:00", 
    "T15:30:00", NA))
expect_equal(iso8601standardise(x, tozulu = FALSE, toymd = FALSE, 
    fillmissing = FALSE), 
  c("2024-01-01T12:34", "2024-W01-1", "2024-123T13:00:00+01:00", 
    "T15:30", NA))

expect_warning(x <- iso8601standardise(c("2024-01", "FOO")))
expect_equal(x, c("2024-01-01", NA))


# Following resulted in segfault in earlier version
expect_error(iso8601standardise("2024", "foo"))
