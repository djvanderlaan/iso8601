#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("Simplify duration P12.5Y", "[removefractions]") {
  Duration d = parseduration("P12.5Y");
  Duration d2 = simplify(d);
  //years
  REQUIRE_FALSE( d2.has_years() );
  // months
  REQUIRE_FALSE( d2.months_fractional() );
  REQUIRE( d2.months() == 150 );
  // days
  REQUIRE_FALSE( d2.has_days() );
  // hours
  REQUIRE_FALSE( d2.has_hours() );
  // minutes
  REQUIRE_FALSE( d2.has_minutes() );
  // seconds
  REQUIRE_FALSE( d2.has_seconds() );
}

TEST_CASE("Simplify duration P12Y1,5M", "[removefractions]") {
  Duration d = parseduration("P12Y1,5M");
  Duration d2 = simplify(d);
  //years
  REQUIRE_FALSE( d2.has_years() );
  // months
  REQUIRE( d2.months_fractional() );
  REQUIRE( d2.months() == 145.5 );
  // days
  REQUIRE_FALSE( d2.has_days() );
  // hours
  REQUIRE_FALSE( d2.has_hours() );
  // minutes
  REQUIRE_FALSE( d2.has_minutes() );
  // seconds
  REQUIRE_FALSE( d2.has_seconds() );
}

TEST_CASE("Simplify duration P3Y2M1D", "[removefractions]") {
  Duration d = parseduration("P3Y2M1D");
  Duration d2 = simplify(d);
  //years
  REQUIRE_FALSE( d2.has_years() );
  // months
  REQUIRE_FALSE( d2.months_fractional() );
  REQUIRE( d2.months() == 38 );
  // days
  REQUIRE_FALSE( d2.has_days() );
  // hours
  REQUIRE_FALSE( d2.has_hours() );
  // minutes
  REQUIRE_FALSE( d2.has_minutes() );
  // seconds
  REQUIRE( d2.has_seconds() );
  REQUIRE_FALSE( d2.seconds_fractional() );
  REQUIRE( d2.seconds() == 24*3600 );
}

TEST_CASE("Simplify duration PT1,5H", "[removefractions]") {
  Duration d = parseduration("PT1,5H");
  Duration d2 = simplify(d);
  //years
  REQUIRE_FALSE( d2.has_years() );
  // months
  REQUIRE_FALSE( d2.has_months() );
  // days
  REQUIRE_FALSE( d2.has_days() );
  // hours
  REQUIRE_FALSE( d2.has_hours() );
  // minutes
  REQUIRE_FALSE( d2.has_minutes() );
  // seconds
  REQUIRE( d2.has_seconds() );
  REQUIRE_FALSE( d2.seconds_fractional() );
  REQUIRE( d2.seconds() == 1.5*3600 );
}

TEST_CASE("Simplify duration PT1H5M20S", "[removefractions]") {
  Duration d = parseduration("PT1H5M20S");
  Duration d2 = simplify(d);
  //years
  REQUIRE_FALSE( d2.has_years() );
  // months
  REQUIRE_FALSE( d2.has_months() );
  // days
  REQUIRE_FALSE( d2.has_days() );
  // hours
  REQUIRE_FALSE( d2.has_hours() );
  // minutes
  REQUIRE_FALSE( d2.has_minutes() );
  // seconds
  REQUIRE( d2.has_seconds() );
  REQUIRE_FALSE( d2.seconds_fractional() );
  REQUIRE( d2.seconds() == 3600+300+20 );
}

TEST_CASE("Simplify duration P1W", "[removefractions]") {
  Duration d = parseduration("P1W");
  Duration d2 = simplify(d);
  //years
  REQUIRE_FALSE( d2.has_years() );
  // months
  REQUIRE_FALSE( d2.has_months() );
  // days
  REQUIRE_FALSE( d2.has_weeks() );
  // days
  REQUIRE_FALSE( d2.has_days() );
  // hours
  REQUIRE_FALSE( d2.has_hours() );
  // minutes
  REQUIRE_FALSE( d2.has_minutes() );
  // seconds
  REQUIRE( d2.has_seconds() );
  REQUIRE_FALSE( d2.seconds_fractional() );
  REQUIRE( d2.seconds() == 7*24*3600 );
}



