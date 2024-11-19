#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("Duration parse P1Y2M3DT4H5M6,7S", "[parseduration]") {
  Duration d = parseduration("P1Y2M3DT4H5M6,7S");
  REQUIRE_FALSE(d.years_fractional());
  REQUIRE(d.yearsv() == 1);
  REQUIRE_FALSE(d.months_fractional());
  REQUIRE(d.monthsv() == 2);
  REQUIRE_FALSE(d.days_fractional());
  REQUIRE(d.daysv() == 3);
  REQUIRE_FALSE(d.hours_fractional());
  REQUIRE(d.hoursv() == 4);
  REQUIRE_FALSE(d.minutes_fractional());
  REQUIRE(d.minutesv() == 5);
  REQUIRE(d.seconds_fractional());
  REQUIRE(d.secondsv() == 6.7);
  REQUIRE_FALSE(d.has_weeks());
  REQUIRE_THROWS(d.weeksv());
}

TEST_CASE("Duration parse PT4H5M6.7S", "[parseduration]") {
  Duration d = parseduration("PT4H5M6.7S");
  REQUIRE_FALSE(d.has_years());
  REQUIRE_FALSE(d.has_months());
  REQUIRE_FALSE(d.has_days());
  REQUIRE_FALSE(d.hours_fractional());
  REQUIRE(d.hoursv() == 4);
  REQUIRE_FALSE(d.minutes_fractional());
  REQUIRE(d.minutesv() == 5);
  REQUIRE(d.seconds_fractional());
  REQUIRE(d.secondsv() == 6.7);
  REQUIRE_THROWS(d.yearsv());
  REQUIRE_THROWS(d.monthsv());
  REQUIRE_THROWS(d.daysv());
  REQUIRE_FALSE(d.has_weeks());
  REQUIRE_THROWS(d.weeksv());
}

TEST_CASE("Duration parse P01Y299M3,4D", "[parseduration]") {
  Duration d = parseduration("P01Y299M3.4D");
  REQUIRE_FALSE(d.years_fractional());
  REQUIRE(d.yearsv() == 1);
  REQUIRE_FALSE(d.months_fractional());
  REQUIRE(d.monthsv() == 299);
  REQUIRE(d.days_fractional());
  REQUIRE(d.daysv() == 3.4);
  REQUIRE_FALSE(d.has_hours());
  REQUIRE_FALSE(d.has_minutes());
  REQUIRE_FALSE(d.has_seconds());
  REQUIRE_THROWS(d.hoursv());
  REQUIRE_THROWS(d.minutesv());
  REQUIRE_THROWS(d.secondsv());
  REQUIRE_FALSE(d.has_weeks());
  REQUIRE_THROWS(d.weeksv());
}

TEST_CASE("Duration parse P99.5W", "[parseduration]") {
  Duration d = parseduration("P99.5W");
  REQUIRE(d.weeks_fractional());
  REQUIRE(d.weeksv() == 99.5);
  REQUIRE_FALSE(d.has_years());
  REQUIRE_FALSE(d.has_months());
  REQUIRE_FALSE(d.has_days());
  REQUIRE_THROWS(d.yearsv());
  REQUIRE_THROWS(d.monthsv());
  REQUIRE_THROWS(d.daysv());
  REQUIRE_FALSE(d.has_hours());
  REQUIRE_FALSE(d.has_minutes());
  REQUIRE_FALSE(d.has_seconds());
  REQUIRE_THROWS(d.hoursv());
  REQUIRE_THROWS(d.minutesv());
  REQUIRE_THROWS(d.secondsv());
}


TEST_CASE("Incorrect durations", "[parsedate]") {
  // wrong order
  REQUIRE_THROWS( parseduration("P2M1Y3DT4H5M6S") );
  REQUIRE_THROWS( parseduration("P1Y3D2MT4H5M6S") );
  REQUIRE_THROWS( parseduration("P1Y2M3DT4M5H6S") );
  REQUIRE_THROWS( parseduration("P1Y2M3DT4H5S6M") );
  // Repeat
  REQUIRE_THROWS( parseduration("P1Y2Y3DT4H5M6S") );
  REQUIRE_THROWS( parseduration("P1Y2M3DT4H5M6M") );
  // date in time and vice versa
  REQUIRE_THROWS( parseduration("P2M3DT4Y5M6S") );
  REQUIRE_THROWS( parseduration("P1Y2MT4H5D6S") );
  REQUIRE_THROWS( parseduration("P1H2M3DT5M6S") );
  REQUIRE_THROWS( parseduration("P1Y2M3ST4H5M") );
  // no T/P
  REQUIRE_THROWS( parseduration("P1Y2M3D4H5M6S") );
  REQUIRE_THROWS( parseduration("P4H5M6S") );
  REQUIRE_THROWS( parseduration("1Y2M3DT4H5M6S") );
  REQUIRE_THROWS( parseduration("P") );
  REQUIRE_THROWS( parseduration("P1") );
  // extra characters
  REQUIRE_THROWS( parseduration(" P1Y2M3DT4H5M6S") );
  REQUIRE_THROWS( parseduration("P1Y2M3DT4H5M6S ") );
  // fraction should be last
  REQUIRE_THROWS( parseduration("P1Y2M3DT4H5.5M6S") );
  REQUIRE_THROWS( parseduration("P1Y2M3DT4.5H5") );
  REQUIRE_THROWS( parseduration("P1Y2M3.5DT4H") );
  REQUIRE_THROWS( parseduration("P1Y2.5M3D") );
  REQUIRE_THROWS( parseduration("P1.4Y2.5M") );
  // weeks cannot be combined with anything else
  REQUIRE_THROWS( parseduration("P1Y99.5W") );
  REQUIRE_THROWS( parseduration("P1M99.5W") );
  REQUIRE_THROWS( parseduration("M99.5WT1H") );
  REQUIRE_THROWS( parseduration("M99.5WT1M") );
  REQUIRE_THROWS( parseduration("M99.5WT1S") );
  REQUIRE_THROWS( parseduration("M99.5WT") );
}


