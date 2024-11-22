#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("Standardise months", "[standardise]") {
  Duration d = parseduration("P12Y20M1DT2H3M4S");
  Duration d2 = standardise(d);

  REQUIRE_FALSE( d2.years_fractional() );
  REQUIRE( d2.years() == 13 );
  REQUIRE_FALSE( d2.months_fractional() );
  REQUIRE( d2.months() == 8 );
  REQUIRE( d2.has_days() );
  REQUIRE_FALSE( d2.days_fractional() );
  REQUIRE( d2.days() == 1 );
  REQUIRE( d2.has_hours() );
  REQUIRE_FALSE( d2.hours_fractional() );
  REQUIRE( d2.hours() == 2 );
  REQUIRE( d2.has_minutes() );
  REQUIRE_FALSE( d2.minutes_fractional() );
  REQUIRE( d2.minutes() == 3 );
  REQUIRE( d2.has_seconds() );
  REQUIRE_FALSE( d2.seconds_fractional() );
  REQUIRE( d2.seconds() == 4 );
}

TEST_CASE("Standardise months zero remain", "[standardise]") {
  Duration d = parseduration("P12Y12M1DT2H3M4S");
  Duration d2 = standardise(d);

  REQUIRE_FALSE( d2.years_fractional() );
  REQUIRE( d2.years() == 13 );
  REQUIRE_FALSE( d2.has_months() );
  REQUIRE( d2.has_days() );
  REQUIRE_FALSE( d2.days_fractional() );
  REQUIRE( d2.days() == 1 );
  REQUIRE( d2.has_hours() );
  REQUIRE_FALSE( d2.hours_fractional() );
  REQUIRE( d2.hours() == 2 );
  REQUIRE( d2.has_minutes() );
  REQUIRE_FALSE( d2.minutes_fractional() );
  REQUIRE( d2.minutes() == 3 );
  REQUIRE( d2.has_seconds() );
  REQUIRE_FALSE( d2.seconds_fractional() );
  REQUIRE( d2.seconds() == 4 );
}

TEST_CASE("Standardise fractional month", "[standardise]") {
  Duration d = parseduration("P12Y12,5M");
  Duration d2 = standardise(d);
  REQUIRE_FALSE( d2.years_fractional() );
  REQUIRE( d2.years() == 13 );
  REQUIRE( d2.has_months() );
  REQUIRE( d2.months_fractional() );
  REQUIRE( d2.months() == 0.5 );
  REQUIRE_FALSE( d2.has_days() );
  //REQUIRE_FALSE( d2.days_fractional() );
  //REQUIRE( d2.days() == 1 );
  REQUIRE_FALSE( d2.has_hours() );
  //REQUIRE_FALSE( d2.hours_fractional() );
  //REQUIRE( d2.hours() == 2 );
  REQUIRE_FALSE( d2.has_minutes() );
  //REQUIRE_FALSE( d2.minutes_fractional() );
  //REQUIRE( d2.minutes() == 3 );
  REQUIRE_FALSE( d2.has_seconds() );
  //REQUIRE_FALSE( d2.seconds_fractional() );
  //REQUIRE( d2.seconds() == 4 );
}

TEST_CASE("Standardise time", "[standardise]") {
  Duration d = parseduration("P1DT23H59M120,5S");
  Duration d2 = standardise(d);
  REQUIRE_FALSE( d2.has_years() );
  REQUIRE_FALSE( d2.has_months() );
  REQUIRE( d2.has_days() );
  REQUIRE_FALSE( d2.days_fractional() );
  REQUIRE( d2.days() == 2 );
  REQUIRE_FALSE( d2.has_hours() );
  REQUIRE( d2.has_minutes() );
  REQUIRE_FALSE( d2.minutes_fractional() );
  REQUIRE( d2.minutes() == 1 );
  REQUIRE( d2.has_seconds() );
  REQUIRE( d2.seconds_fractional() );
  REQUIRE( d2.seconds() == 0.5 );
}

