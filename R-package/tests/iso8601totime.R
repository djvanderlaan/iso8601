library(iso8601)
source("helpers.R")

# Note that testing of the parsing of all of the various date formats allowed in
# ISO8601 is done in the c++ library. We will not test these here. Here we will
# only test if the R-routines correctly call the c++ routines and that the
# result of those calls is handles correctly in R.

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


# Time time = parsetime("T12:23:34");
# Time time = parsetime("T122334");
# Time time = parsetime("T12");
# Time time = parsetime("T12.123");
# Time time = parsetime("T12:23,123");
# Time time = parsetime("T1223.123");
# Time time = parsetime("T1223");
# Time time = parsetime("T12:23:34.123");
# Time time = parsetime("T122334,123");
# REQUIRE_THROWS( parsetime("T") );
# REQUIRE_THROWS( parsetime("T1") );
# REQUIRE_THROWS( parsetime("T12:2334") );
# REQUIRE_THROWS( parsetime("T1223:34") );
# REQUIRE_THROWS( parsetime("T12:23.1:34") );
# REQUIRE_THROWS( parsetime("T12:23:34.") );
# REQUIRE_THROWS( parsetime("T12:23:34 ") );
# REQUIRE_THROWS( parsetime(" T12:23:34 ") );
# REQUIRE_THROWS( parsetime("T12:23:60") );
# REQUIRE_THROWS( parsetime("T12:60:34") );
# REQUIRE_THROWS( parsetime("T25:23:34") );
# REQUIRE_THROWS( parsetime("T24:23:34") );
# Time time = parsetime("T12:23:34Z");
# Time time = parsetime("T12:23:34+01");
# Time time = parsetime("T12:23:34+0100");
# Time time = parsetime("T12:23:34-03:30");
# Time time = parsetime("T12:23:34.123Z");
# Time time = parsetime("T12:23.123-03:30");
# // this is unicode minus instead of hyphen-minus
# Time time = parsetime("T12:23.123−03:30");
# Time time = parsetime("T12+01:00");
# Time time = parsetime("T122334+0100");
# Time time = parsetime("T122334±00:00");
# REQUIRE_THROWS( parsetime("T12:23:34X") );
# REQUIRE_THROWS( parsetime("T12:23:34+1") );
# REQUIRE_THROWS( parsetime("T12:23:34+01.5") );
# REQUIRE_THROWS( parsetime("T12:23:34+01:5") );
# REQUIRE_THROWS( parsetime("T12:23:34+015") );
# REQUIRE_THROWS( parsetime("T12:23:34-") );
# REQUIRE_THROWS( parsetime("T12:23:34+13") );
# REQUIRE_THROWS( parsetime("T12:23:34-13") );
# REQUIRE_THROWS( parsetime("T12:23:34+03:63") );
# REQUIRE_THROWS( parsetime("T12:23:34+03:60") );
# REQUIRE_THROWS( parsetime("T12:23:34-03:-1") );
# REQUIRE_THROWS( parsetime("T12:23:34-03:-10") );
# REQUIRE_THROWS( parsetime("T12:23:34+12:01") );
# REQUIRE_THROWS( parsetime("T12:23:34-12:01") );
# REQUIRE_THROWS( parsetime("T12:23:34±01:00") );
# Time time = parsetime("12:23:34");
# Time time = parsetime("12:23");
# Time time = parsetime("122334", true);
# Time time = parsetime("12.123", true);
# REQUIRE_THROWS( parsetime("122334") );
# REQUIRE_THROWS( parsetime("1223") );
# REQUIRE_THROWS( parsetime("12") );
# REQUIRE_THROWS( parsetime("1") );
