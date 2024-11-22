#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("Remove fractions from duration P12.5Y", "[removefractions]") {
  Duration d = parseduration("P12.5Y");
  Duration d2 = removefractions(d);

  REQUIRE_FALSE( d2.years_fractional() );
  REQUIRE( d2.years() == 12 );
  REQUIRE_FALSE( d2.months_fractional() );
  REQUIRE( d2.months() == 6 );
  REQUIRE_FALSE( d2.has_days() );
  REQUIRE_FALSE( d2.has_hours() );
  REQUIRE_FALSE( d2.has_minutes() );
  REQUIRE_FALSE( d2.has_seconds() );
}

TEST_CASE("Remove fractions from duration P12.55Y", "[removefractions]") {
  Duration d = parseduration("P12.55Y");
  Duration d2 = removefractions(d);

  REQUIRE_FALSE( d2.years_fractional() );
  REQUIRE( d2.years() == 12 );
  REQUIRE( d2.months_fractional() );
  REQUIRE_THAT( d2.months(), Catch::Matchers::WithinAbs(6.6, 0.001) );
  REQUIRE_FALSE( d2.has_days() );
  REQUIRE_FALSE( d2.has_hours() );
  REQUIRE_FALSE( d2.has_minutes() );
  REQUIRE_FALSE( d2.has_seconds() );
}

TEST_CASE("Remove fractions from duration month precision", "[removefractions]") {
  Duration d = parseduration("P12.51Y");
  Duration d2 = removefractions(d, true, 0.2);

  REQUIRE_FALSE( d2.years_fractional() );
  REQUIRE( d2.years() == 12 );
  REQUIRE_FALSE( d2.months_fractional() );
  REQUIRE( d2.months() == 6 );
  REQUIRE_FALSE( d2.has_days() );
  REQUIRE_FALSE( d2.has_hours() );
  REQUIRE_FALSE( d2.has_minutes() );
  REQUIRE_FALSE( d2.has_seconds() );
}

TEST_CASE("Remove fractions from duration P1.5D", "[removefractions]") {
  Duration d = parseduration("P1.5D");
  Duration d2 = removefractions(d);

  REQUIRE_FALSE( d2.has_years() );
  REQUIRE_FALSE( d2.has_months() );
  REQUIRE( d2.has_days() );
  REQUIRE( d2.days() == 1 );
  REQUIRE_FALSE( d2.days_fractional() );
  REQUIRE( d2.has_hours() );
  REQUIRE( d2.hours() == 12 );
  REQUIRE_FALSE( d2.hours_fractional() );
  REQUIRE_FALSE( d2.has_minutes() );
  REQUIRE_FALSE( d2.has_seconds() );
}

TEST_CASE("Remove fractions from duration P1.57D", "[removefractions]") {
  Duration d = parseduration("P0.57D");
  Duration d2 = removefractions(d);

  REQUIRE_FALSE( d2.has_years() );
  REQUIRE_FALSE( d2.has_months() );
  REQUIRE_FALSE( d2.has_days() );
  REQUIRE( d2.has_hours() );
  REQUIRE( d2.hours() == 13 );
  REQUIRE_FALSE( d2.hours_fractional() );
  REQUIRE( d2.has_minutes() );
  REQUIRE( d2.minutes() == 40 );
  REQUIRE_FALSE( d2.minutes_fractional() );
  REQUIRE( d2.has_seconds() );
  REQUIRE_THAT( d2.seconds(), Catch::Matchers::WithinAbs(48, 0.001) );
  REQUIRE( d2.seconds_fractional() );
}

TEST_CASE("Remove fractions from duration round seconds", "[removefractions]") {
  Duration d = parseduration("P0.57D");
  Duration d2 = removefractions(d, true);

  REQUIRE_FALSE( d2.has_years() );
  REQUIRE_FALSE( d2.has_months() );
  REQUIRE_FALSE( d2.has_days() );
  REQUIRE( d2.has_hours() );
  REQUIRE( d2.hours() == 13 );
  REQUIRE_FALSE( d2.hours_fractional() );
  REQUIRE( d2.has_minutes() );
  REQUIRE( d2.minutes() == 40 );
  REQUIRE_FALSE( d2.minutes_fractional() );
  REQUIRE( d2.has_seconds() );
  REQUIRE( d2.seconds() == 48 );
  REQUIRE_FALSE( d2.seconds_fractional() );
}

TEST_CASE("Remove fractions from duration zero", "[removefractions]") {
  Duration d = parseduration("P0.000Y");
  Duration d2 = removefractions(d, true);

  REQUIRE_FALSE( d2.has_years() );
  REQUIRE_FALSE( d2.has_months() );
  REQUIRE_FALSE( d2.has_days() );
  REQUIRE_FALSE( d2.has_hours() );
  REQUIRE_FALSE( d2.has_minutes() );
  REQUIRE( d2.has_seconds() );
  REQUIRE( d2.seconds() == 0 );
  REQUIRE_FALSE( d2.seconds_fractional() );
}

TEST_CASE("Remove fractions from weeks no fraction", "[removefractions]") {
  Duration d = parseduration("P5W");
  Duration d2 = removefractions(d, true);

  REQUIRE_FALSE( d2.has_years() );
  REQUIRE_FALSE( d2.has_months() );
  REQUIRE_FALSE( d2.has_days() );
  REQUIRE_FALSE( d2.has_hours() );
  REQUIRE_FALSE( d2.has_minutes() );
  REQUIRE_FALSE( d2.has_seconds() );
  REQUIRE_FALSE( d2.weeks_fractional() );
  REQUIRE( d2.weeks() == 5 );
}

TEST_CASE("Remove fractions from weeks", "[removefractions]") {
  Duration d = parseduration("P5,5W");
  Duration d2 = removefractions(d, true);

  REQUIRE_FALSE( d2.has_years() );
  REQUIRE_FALSE( d2.has_months() );
  REQUIRE( d2.has_days() );
  REQUIRE_FALSE( d2.days_fractional() );
  REQUIRE( d2.days() == 38 );
  REQUIRE( d2.has_hours() );
  REQUIRE_FALSE( d2.hours_fractional() );
  REQUIRE( d2.hours() == 12 );
  REQUIRE_FALSE( d2.has_minutes() );
  REQUIRE_FALSE( d2.has_seconds() );
  REQUIRE_FALSE( d2.has_weeks() );
}

