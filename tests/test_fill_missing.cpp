#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("Fill missing THH:MM", "[fill_missing]") {
  Time time = parsetime("T12:23");
  Time time2 = fill_missing(time);
  REQUIRE_FALSE( time2.hour_fractional() );
  REQUIRE( time2.hour() == 12 );
  REQUIRE( time2.has_minutes() );
  REQUIRE_FALSE( time2.minutes_fractional() );
  REQUIRE( time2.minutes() == 23);
  REQUIRE( time2.has_seconds() );
  REQUIRE_FALSE( time2.seconds_fractional() );
  REQUIRE( time2.seconds() == 0);
}

TEST_CASE("Fill missing THH", "[fill_missing]") {
  Time time = parsetime("T12");
  Time time2 = fill_missing(time);
  REQUIRE_FALSE( time2.hour_fractional() );
  REQUIRE( time2.hour() == 12 );
  REQUIRE( time2.has_minutes() );
  REQUIRE_FALSE( time2.minutes_fractional() );
  REQUIRE( time2.minutes() == 0);
  REQUIRE( time2.has_seconds() );
  REQUIRE_FALSE( time2.seconds_fractional() );
  REQUIRE( time2.seconds() == 0);
}


TEST_CASE("Fill missing THH.hhh", "[remove_fractions]") {
  Time time = parsetime("T12.553");
  Time time2 = fill_missing(time);
  REQUIRE_FALSE( time2.hour_fractional() );
  REQUIRE( time2.hour() == 12 );
  REQUIRE( time2.has_minutes() );
  REQUIRE_FALSE( time2.minutes_fractional() );
  REQUIRE( time2.minutes() == 33);
  REQUIRE( time2.has_seconds() );
  REQUIRE( time2.seconds_fractional() );
  REQUIRE_THAT( time2.seconds(), Catch::Matchers::WithinAbs(10.8, 1E-10) );
}

