
#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("Time parsing THH:MM:SS", "[parsetime]") {
  Time time = parsetime("T12:23:34");
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

TEST_CASE("Time parsing THHMMSS", "[parsetime]") {
  Time time = parsetime("T122334");
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

TEST_CASE("Time parsing THH", "[parsetime]") {
  Time time = parsetime("T12");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE_FALSE( time.has_minutes() );
  REQUIRE_THROWS( time.minutes() == 23 );
  REQUIRE_THROWS( time.minutes_fractional() );
  REQUIRE_FALSE( time.has_seconds() );
  REQUIRE_THROWS( time.seconds() == 34 );
  REQUIRE_THROWS( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Time parsing THH.hhh", "[parsetime]") {
  Time time = parsetime("T12.123");
  REQUIRE( time.hour() == 12.123 );
  REQUIRE( time.hour_fractional()  );
  REQUIRE_FALSE( time.has_minutes() );
  REQUIRE_THROWS( time.minutes() == 23 );
  REQUIRE_THROWS( time.minutes_fractional() );
  REQUIRE_FALSE( time.has_seconds() );
  REQUIRE_THROWS( time.seconds() == 34 );
  REQUIRE_THROWS( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Time parsing THH:MM,mmm", "[parsetime]") {
  Time time = parsetime("T12:23,123");
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

TEST_CASE("Time parsing THHMM.mmm", "[parsetime]") {
  Time time = parsetime("T1223.123");
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

TEST_CASE("Time parsing THHMM", "[parsetime]") {
  Time time = parsetime("T1223");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  REQUIRE_FALSE( time.has_seconds() );
  REQUIRE_THROWS( time.seconds() == 34 );
  REQUIRE_THROWS( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Time parsing THH:MM:SS.sss", "[parsetime]") {
  Time time = parsetime("T12:23:34.123");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  REQUIRE( time.has_seconds() );
  REQUIRE( time.seconds() == 34.123 );
  REQUIRE( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Time parsing THHMMSS,sss", "[parsetime]") {
  Time time = parsetime("T122334,123");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  REQUIRE( time.has_seconds() );
  REQUIRE( time.seconds() == 34.123 );
  REQUIRE( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Time parsing invalid cases", "[parsetime]") {
  REQUIRE_THROWS( parsetime("T") );
  REQUIRE_THROWS( parsetime("T1") );
  REQUIRE_THROWS( parsetime("T12:2334") );
  REQUIRE_THROWS( parsetime("T1223:34") );
  REQUIRE_THROWS( parsetime("T12:23.1:34") );
  REQUIRE_THROWS( parsetime("T12:23:34.") );
  REQUIRE_THROWS( parsetime("T12:23:34 ") );
  REQUIRE_THROWS( parsetime(" T12:23:34 ") );
  REQUIRE_THROWS( parsetime("T12:23:60") );
  REQUIRE_THROWS( parsetime("T12:60:34") );
  REQUIRE_THROWS( parsetime("T25:23:34") );
  REQUIRE_THROWS( parsetime("T24:23:34") );
}

TEST_CASE("Time parsing THH:MM:SSZ", "[parsetime]") {
  Time time = parsetime("T12:23:34Z");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  REQUIRE( time.has_seconds() );
  REQUIRE( time.seconds() == 34 );
  REQUIRE_FALSE( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Time parsing THH:MM:SS+01", "[parsetime]") {
  Time time = parsetime("T12:23:34+01");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  REQUIRE( time.has_seconds() );
  REQUIRE( time.seconds() == 34 );
  REQUIRE_FALSE( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 1 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Time parsing THH:MM:SS+0100", "[parsetime]") {
  Time time = parsetime("T12:23:34+0100");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  REQUIRE( time.has_seconds() );
  REQUIRE( time.seconds() == 34 );
  REQUIRE_FALSE( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 1 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Time parsing THH:MM:SS-03:30", "[parsetime]") {
  Time time = parsetime("T12:23:34-03:30");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  REQUIRE( time.has_seconds() );
  REQUIRE( time.seconds() == 34 );
  REQUIRE_FALSE( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == -3 );
  REQUIRE( tz.offset_minutes() == 30 );
}

TEST_CASE("Time parsing THH:MM:SS.sssZ", "[parsetime]") {
  Time time = parsetime("T12:23:34.123Z");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  REQUIRE( time.has_seconds() );
  REQUIRE( time.seconds() == 34.123 );
  REQUIRE( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Time parsing THH:MM.mmm-03:30", "[parsetime]") {
  Time time = parsetime("T12:23.123-03:30");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23.123 );
  REQUIRE( time.minutes_fractional() );
  REQUIRE_FALSE( time.has_seconds() );
  REQUIRE_THROWS( time.seconds() == 34 );
  REQUIRE_THROWS( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == -3 );
  REQUIRE( tz.offset_minutes() == 30 );
}

TEST_CASE("Time parsing THH:MM.mmm−03:30", "[parsetime]") {
  // this is unicode minus instead of hyphen-minus
  Time time = parsetime("T12:23.123−03:30");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23.123 );
  REQUIRE( time.minutes_fractional() );
  REQUIRE_FALSE( time.has_seconds() );
  REQUIRE_THROWS( time.seconds() == 34 );
  REQUIRE_THROWS( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == -3 );
  REQUIRE( tz.offset_minutes() == 30 );
}


TEST_CASE("Time parsing THH+01:00", "[parsetime]") {
  Time time = parsetime("T12+01:00");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE_FALSE( time.has_minutes() );
  REQUIRE_THROWS( time.minutes() == 23.123 );
  REQUIRE_THROWS( time.minutes_fractional() );
  REQUIRE_FALSE( time.has_seconds() );
  REQUIRE_THROWS( time.seconds() == 34 );
  REQUIRE_THROWS( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 1 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Time parsing THHMMSS+0100", "[parsetime]") {
  Time time = parsetime("T122334+0100");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  REQUIRE( time.has_seconds() );
  REQUIRE( time.seconds() == 34 );
  REQUIRE_FALSE( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 1 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Time parsing THHMMSS±00:00", "[parsetime]") {
  Time time = parsetime("T122334±00:00");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  REQUIRE( time.has_seconds() );
  REQUIRE( time.seconds() == 34 );
  REQUIRE_FALSE( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE_FALSE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}


TEST_CASE("Time parsing invalid time zones", "[parsetime]") {
  REQUIRE_THROWS( parsetime("T12:23:34X") );
  REQUIRE_THROWS( parsetime("T12:23:34+1") );
  REQUIRE_THROWS( parsetime("T12:23:34+01.5") );
  REQUIRE_THROWS( parsetime("T12:23:34+01:5") );
  REQUIRE_THROWS( parsetime("T12:23:34+015") );
  REQUIRE_THROWS( parsetime("T12:23:34-") );
  REQUIRE_THROWS( parsetime("T12:23:34+13") );
  REQUIRE_THROWS( parsetime("T12:23:34-13") );
  REQUIRE_THROWS( parsetime("T12:23:34+03:63") );
  REQUIRE_THROWS( parsetime("T12:23:34+03:60") );
  REQUIRE_THROWS( parsetime("T12:23:34-03:-1") );
  REQUIRE_THROWS( parsetime("T12:23:34-03:-10") );
  REQUIRE_THROWS( parsetime("T12:23:34+12:01") );
  REQUIRE_THROWS( parsetime("T12:23:34-12:01") );
  REQUIRE_THROWS( parsetime("T12:23:34±01:00") );
}

// ============================================================================
// Test cases without T

TEST_CASE("Time parsing HH:MM:SS", "[parsetime]") {
  Time time = parsetime("12:23:34");
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

TEST_CASE("Time parsing HH:MM", "[parsetime]") {
  Time time = parsetime("12:23");
  REQUIRE( time.hour() == 12 );
  REQUIRE_FALSE( time.hour_fractional()  );
  REQUIRE( time.has_minutes() );
  REQUIRE( time.minutes() == 23 );
  REQUIRE_FALSE( time.minutes_fractional() );
  REQUIRE_FALSE( time.has_seconds() );
  Timezone tz = time.timezone();
  REQUIRE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Time parsing HHMMSS", "[parsetime]") {
  Time time = parsetime("122334", true);
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

TEST_CASE("Time parsing HH.hhh", "[parsetime]") {
  Time time = parsetime("12.123", true);
  REQUIRE( time.hour() == 12.123 );
  REQUIRE( time.hour_fractional()  );
  REQUIRE_FALSE( time.has_minutes() );
  REQUIRE_THROWS( time.minutes() == 23 );
  REQUIRE_THROWS( time.minutes_fractional() );
  REQUIRE_FALSE( time.has_seconds() );
  REQUIRE_THROWS( time.seconds() == 34 );
  REQUIRE_THROWS( time.seconds_fractional() );
  Timezone tz = time.timezone();
  REQUIRE( tz.localtime() );
  REQUIRE( tz.offset_hours() == 0 );
  REQUIRE( tz.offset_minutes() == 0 );
}

TEST_CASE("Time parsing invalid cases without T", "[parsetime]") {
  REQUIRE_THROWS( parsetime("122334") );
  REQUIRE_THROWS( parsetime("1223") );
  REQUIRE_THROWS( parsetime("12") );
  REQUIRE_THROWS( parsetime("1") );
}

