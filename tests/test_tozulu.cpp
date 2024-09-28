#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("Convert datetime to zulu; local time", "[tozulu]") {
  Datetime dt = tozulu(parsedatetime("2022-12-22T12:23:00"));
  // does nothing
  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 12 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 22 );
  Time time = dt.time();
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  Timezone tz = time.timezone();
  REQUIRE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Convert datetime to zulu; zulu time", "[tozulu]") {
  Datetime dt = tozulu(parsedatetime("2022-12-22T12:23:00Z"));
  // does nothing
  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 12 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 22 );
  Time time = dt.time();
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Convert datetime to zulu; regular pos", "[tozulu]") {
  Datetime dt = tozulu(parsedatetime("2022-12-22T12:23:00+01:10"));
  // does nothing
  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 12 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 22 );
  Time time = dt.time();
  REQUIRE( time.hour() == 11 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 13 );
  REQUIRE_FALSE( time.minutes_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Convert datetime to zulu; regular neg", "[tozulu]") {
  Datetime dt = tozulu(parsedatetime("2022-12-22T12:23:00-01:10"));
  // does nothing
  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 12 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 22 );
  Time time = dt.time();
  REQUIRE( time.hour() == 13 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 33 );
  REQUIRE_FALSE( time.minutes_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Convert datetime to zulu; year crossing", "[tozulu]") {
  Datetime dt = tozulu(parsedatetime("2022-01-01T01:03:00+02:10"));
  // does nothing
  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2021 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 12 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 31 );
  Time time = dt.time();
  REQUIRE( time.hour() == 22 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 53 );
  REQUIRE_FALSE( time.minutes_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Convert datetime to zulu; leap year neg", "[tozulu]") {
  Datetime dt = tozulu(parsedatetime("2024-03-01T01:03:00+02:10"));
  // does nothing
  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2024 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 2 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 29 );
  Time time = dt.time();
  REQUIRE( time.hour() == 22 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 53 );
  REQUIRE_FALSE( time.minutes_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Convert datetime to zulu; non leap year neg", "[tozulu]") {
  Datetime dt = tozulu(parsedatetime("2022-03-01T01:03:00+02:10"));
  // does nothing
  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 2 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 28 );
  Time time = dt.time();
  REQUIRE( time.hour() == 22 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 53 );
  REQUIRE_FALSE( time.minutes_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Convert datetime to zulu; leap year pos", "[tozulu]") {
  Datetime dt = tozulu(parsedatetime("2024-02-28T22:53:00-02:10"));
  // does nothing
  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2024 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 2 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 29 );
  Time time = dt.time();
  REQUIRE( time.hour() == 1 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 3 );
  REQUIRE_FALSE( time.minutes_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Convert datetime to zulu; non leap year pos", "[tozulu]") {
  Datetime dt = tozulu(parsedatetime("2022-02-28T22:53:00-02:10"));
  // does nothing
  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 3 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 1 );
  Time time = dt.time();
  REQUIRE( time.hour() == 1 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 3 );
  REQUIRE_FALSE( time.minutes_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Convert datetime YYYY-DDD to zulu; year crossing", "[tozulu]") {
  Datetime dt = tozulu(parsedatetime("2022-001T01:03:00+02:10"));
  // does nothing
  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARDAY );
  REQUIRE( date.year() == 2021 );
  REQUIRE( date.has_yearday()  );
  REQUIRE( date.yearday() == 365 );
  Time time = dt.time();
  REQUIRE( time.hour() == 22 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 53 );
  REQUIRE_FALSE( time.minutes_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Convert datetime YYYY-DDD to zulu; leap year crossing", "[tozulu]") {
  Datetime dt = tozulu(parsedatetime("2025-001T01:03:00+02:10"));
  // does nothing
  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARDAY );
  REQUIRE( date.year() == 2024 );
  REQUIRE( date.has_yearday()  );
  REQUIRE( date.yearday() == 366 );
  Time time = dt.time();
  REQUIRE( time.hour() == 22 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 53 );
  REQUIRE_FALSE( time.minutes_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Convert datetime YYYY-DDD to zulu; leap year non crossing", "[tozulu]") {
  Datetime dt = tozulu(parsedatetime("2024-365T22:53:00-02:10"));
  // does nothing
  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARDAY );
  REQUIRE( date.year() == 2024 );
  REQUIRE( date.has_yearday()  );
  REQUIRE( date.yearday() == 366 );
  Time time = dt.time();
  REQUIRE( time.hour() == 1 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 3 );
  REQUIRE_FALSE( time.minutes_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Convert datetime YYYY-DDD to zulu; day crossing", "[tozulu]") {
  Datetime dt = tozulu(parsedatetime("2024-065T22:53:00-02:10"));
  // does nothing
  Date date = dt.date();
  REQUIRE( date.type() == Date::YEARDAY );
  REQUIRE( date.year() == 2024 );
  REQUIRE( date.has_yearday()  );
  REQUIRE( date.yearday() == 66 );
  Time time = dt.time();
  REQUIRE( time.hour() == 1 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 3 );
  REQUIRE_FALSE( time.minutes_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Convert datatime to zulu invalid cases", "[tozulu]") {
  // weeks do not work yet
  REQUIRE_THROWS( tozulu(parsedatetime("2024-W01-1T22:53:00-02:10")) );
  // incomplete date or time
  REQUIRE_THROWS( tozulu(parsedatetime("2024-12T22:53:00-02:10")) );
  REQUIRE_THROWS( tozulu(parsedatetime("2024-12-12T22-02:10")) );
  REQUIRE_THROWS( tozulu(parsedatetime("2024-12-12T22-02")) );
}

