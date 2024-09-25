#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("Remove fractions from time THH:MM.mmm", "[remove_fractions]") {
  Time time = parsetime("T12:23.555");
  Time time2 = remove_fractions(time);
  REQUIRE_FALSE( time2.minutes_fractional() );
  REQUIRE( time2.minutes() == 23);
  REQUIRE( time2.has_seconds() );
  REQUIRE( time2.seconds_fractional() );
  REQUIRE_THAT( time2.seconds(), Catch::Matchers::WithinAbs(33.3, 1E-10) );

  Time time3 = remove_fractions(time, true);
  REQUIRE_FALSE( time3.minutes_fractional() );
  REQUIRE( time3.minutes() == 23);
  REQUIRE( time3.has_seconds() );
  REQUIRE_FALSE( time3.seconds_fractional() );
  REQUIRE( time3.seconds() == 33 );
}

TEST_CASE("Remove fractions from time THH.hhh", "[remove_fractions]") {
  Time time = parsetime("T12.553");
  Time time2 = remove_fractions(time);
  REQUIRE_FALSE( time2.hour_fractional() );
  REQUIRE( time2.hour() == 12 );
  REQUIRE( time2.has_minutes() );
  REQUIRE_FALSE( time2.minutes_fractional() );
  REQUIRE( time2.minutes() == 33);
  REQUIRE( time2.has_seconds() );
  REQUIRE( time2.seconds_fractional() );
  REQUIRE_THAT( time2.seconds(), Catch::Matchers::WithinAbs(10.8, 1E-10) );

  Time time3 = remove_fractions(time, true);
  REQUIRE_FALSE( time3.hour_fractional() );
  REQUIRE( time3.hour() == 12 );
  REQUIRE( time3.has_minutes() );
  REQUIRE_FALSE( time3.minutes_fractional() );
  REQUIRE( time3.minutes() == 33);
  REQUIRE( time3.has_seconds() );
  REQUIRE_FALSE( time3.seconds_fractional() );
  REQUIRE( time3.seconds() == 11 );
}

