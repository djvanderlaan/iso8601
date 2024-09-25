#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("Fill missing THH:MM", "[fillmissing]") {
  Time time = parsetime("T12:23");
  Time time2 = fillmissing(time);
  REQUIRE_FALSE( time2.hour_fractional() );
  REQUIRE( time2.hour() == 12 );
  REQUIRE( time2.has_minutes() );
  REQUIRE_FALSE( time2.minutes_fractional() );
  REQUIRE( time2.minutes() == 23);
  REQUIRE( time2.has_seconds() );
  REQUIRE_FALSE( time2.seconds_fractional() );
  REQUIRE( time2.seconds() == 0);
}

TEST_CASE("Fill missing THH", "[fillmissing]") {
  Time time = parsetime("T12");
  Time time2 = fillmissing(time);
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
  Time time2 = fillmissing(time);
  REQUIRE_FALSE( time2.hour_fractional() );
  REQUIRE( time2.hour() == 12 );
  REQUIRE( time2.has_minutes() );
  REQUIRE_FALSE( time2.minutes_fractional() );
  REQUIRE( time2.minutes() == 33);
  REQUIRE( time2.has_seconds() );
  REQUIRE( time2.seconds_fractional() );
  REQUIRE_THAT( time2.seconds(), Catch::Matchers::WithinAbs(10.8, 1E-10) );
}

TEST_CASE("Fill missing YYYY", "[fillmissing]") {
  Date date = parsedate("2022");
  Date date2 = fillmissing(date);
  REQUIRE( date2.type() == Date::YEARMONTHDAY );
  REQUIRE( date2.year() == 2022 );
  REQUIRE( date2.has_month()  );
  REQUIRE( date2.month() == 01 );
  REQUIRE( date2.has_day()  );
  REQUIRE( date2.day() == 01 );
  REQUIRE_FALSE( date2.has_week() );
  REQUIRE_THROWS( date2.week() ); 
  REQUIRE_FALSE( date2.has_weekday() );
  REQUIRE_THROWS( date2.weekday() ); 
  REQUIRE_FALSE( date2.has_yearday() );
  REQUIRE_THROWS( date2.yearday() ); 
}

TEST_CASE("Fill missing YYYY-MM", "[fillmissing]") {
  Date date = parsedate("2022-12");
  Date date2 = fillmissing(date);
  REQUIRE( date2.type() == Date::YEARMONTHDAY );
  REQUIRE( date2.year() == 2022 );
  REQUIRE( date2.has_month()  );
  REQUIRE( date2.month() == 12 );
  REQUIRE( date2.has_day()  );
  REQUIRE( date2.day() == 1 );
  REQUIRE_FALSE( date2.has_week() );
  REQUIRE_THROWS( date2.week() ); 
  REQUIRE_FALSE( date2.has_weekday() );
  REQUIRE_THROWS( date2.weekday() ); 
  REQUIRE_FALSE( date2.has_yearday() );
  REQUIRE_THROWS( date2.yearday() ); 
}

TEST_CASE("Fill missing YYYY-Www", "[fillmissing]") {
  Date date = parsedate("2022-W12");
  Date date2 = fillmissing(date);
  REQUIRE( date2.type() == Date::YEARWEEKDAY );
  REQUIRE( date2.year() == 2022 );
  REQUIRE_FALSE( date2.has_month()  );
  REQUIRE_THROWS( date2.month() );
  REQUIRE_FALSE( date2.has_day()  );
  REQUIRE_THROWS( date2.day() );
  REQUIRE( date2.has_week() );
  REQUIRE( date2.week() == 12 ); 
  REQUIRE( date2.has_weekday() );
  REQUIRE( date2.weekday() == 1 ); 
  REQUIRE_FALSE( date2.has_yearday() );
  REQUIRE_THROWS( date2.yearday() ); 
}

