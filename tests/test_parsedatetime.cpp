#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("Datetime parsing YYYY-MM-DDTHH:MM:SS", "[parsedatetime]") {
  Datetime dt = parsedatetime("2022-12-22T12:23:34");

  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 12 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 22 );
  REQUIRE_FALSE( date.has_week() );
  REQUIRE_THROWS( date.week() ); 
  REQUIRE_FALSE( date.has_weekday() );
  REQUIRE_THROWS( date.weekday() ); 
  REQUIRE_FALSE( date.has_yearday() );
  REQUIRE_THROWS( date.yearday() ); 

  Time time = dt.time();
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  REQUIRE( time.has_seconds() );
  REQUIRE( time.seconds() == 34 );
  REQUIRE_FALSE( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Datetime parsing YYYY-Www-D HH:MM.mmm", "[parsedatetime]") {
  Datetime dt = parsedatetime("2022-W12-3 12:23.123");

  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARWEEKDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_week() );
  REQUIRE( date.week() == 12); 
  REQUIRE( date.has_weekday() );
  REQUIRE( date.weekday() == 3); 
  REQUIRE_FALSE( date.has_month()  );
  REQUIRE_THROWS( date.month() == 12 );
  REQUIRE_FALSE( date.has_day()  );
  REQUIRE_THROWS( date.day() == 22 );
  REQUIRE_FALSE( date.has_yearday() );
  REQUIRE_THROWS( date.yearday() == 123); 

  Time time = dt.time();
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23.123 );
  REQUIRE( time.minutes_fractional() );
  REQUIRE_FALSE( time.has_seconds() );
  REQUIRE_THROWS( time.seconds() == 34 );
  REQUIRE_THROWS( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Datetime parsing YYYY-DDDTHHZ", "[parsedatetime]") {
  Datetime dt = parsedatetime("2022-123T12Z");

  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_yearday() );
  REQUIRE( date.yearday() == 123); 
  REQUIRE_FALSE( date.has_month()  );
  REQUIRE_THROWS( date.month() == 12 );
  REQUIRE_FALSE( date.has_day()  );
  REQUIRE_THROWS( date.day() == 22 );
  REQUIRE_FALSE( date.has_week() );
  REQUIRE_THROWS( date.week() ); 
  REQUIRE_FALSE( date.has_weekday() );
  REQUIRE_THROWS( date.weekday() ); 

  Time time = dt.time();
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE_FALSE( time.has_minutes() );
  REQUIRE_THROWS( time.minutes() == 23 );
  REQUIRE_THROWS( time.minutes_fractional() );
  REQUIRE_FALSE( time.has_seconds() );
  REQUIRE_THROWS( time.seconds() == 34 );
  REQUIRE_THROWS( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Datetime parsing +YYYYYY-MM-DDTHH:MM:SS", "[parsedatetime]") {
  Datetime dt = parsedatetime("+002022-12-22T12:23:34", 2);

  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 12 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 22 );
  REQUIRE_FALSE( date.has_week() );
  REQUIRE_THROWS( date.week() ); 
  REQUIRE_FALSE( date.has_weekday() );
  REQUIRE_THROWS( date.weekday() ); 
  REQUIRE_FALSE( date.has_yearday() );
  REQUIRE_THROWS( date.yearday() ); 

  Time time = dt.time();
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  REQUIRE( time.has_seconds() );
  REQUIRE( time.seconds() == 34 );
  REQUIRE_FALSE( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}


TEST_CASE("Datetime parsing invalid dates", "[parsedatetime]") {
  REQUIRE_THROWS( parsedatetime("2021-12T14:23:23") );
  REQUIRE_THROWS( parsedatetime(" 2021-12-23T14:23:23") );
  REQUIRE_THROWS( parsedatetime("2021-12-23T14:23:23 ") );
  REQUIRE_THROWS( parsedatetime("2021-12-23T14:23:23/2021-12-23T14:25:00") );
  REQUIRE_THROWS( parsedatetime("2021-12-23") );
  REQUIRE_THROWS( parsedatetime("2021-12-23/2021-12-25") );
  REQUIRE_THROWS( parsedatetime("2021-12-23/2021-12-25") );
  REQUIRE_THROWS( parsedatetime("002022-12-22T12:23:34", 2) );
  REQUIRE_THROWS( parsedatetime("002022-12-22T12:23:34", 1) );
}


