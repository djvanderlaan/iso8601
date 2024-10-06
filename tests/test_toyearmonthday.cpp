#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("To year month day YEARDAY", "[toyearmonthday]") {

  Date date = parsedate("2024-123");
  Date date2 = toyearmonthday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARMONTHDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.month() == 5);
  REQUIRE(date2.day() == 2);

  date = parsedate("2024-182");
  date2 = toyearmonthday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARMONTHDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.month() == 6);
  REQUIRE(date2.day() == 30);

  date = parsedate("2023-182");
  date2 = toyearmonthday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARMONTHDAY);
  REQUIRE(date2.year() == 2023);
  REQUIRE(date2.month() == 7);
  REQUIRE(date2.day() == 1);
}

TEST_CASE("To year month day YEARMONTHDAY", "[toyearmonthday]") {

  Date date = parsedate("2024-05-02");
  Date date2 = toyearmonthday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARMONTHDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.month() == 5);
  REQUIRE(date2.day() == 2);

  date = parsedate("2024-06-30");
  date2 = toyearmonthday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARMONTHDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.month() == 6);
  REQUIRE(date2.day() == 30);

  date = parsedate("2023-07-01");
  date2 = toyearmonthday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARMONTHDAY);
  REQUIRE(date2.year() == 2023);
  REQUIRE(date2.month() == 7);
  REQUIRE(date2.day() == 1);

  date = parsedate("2023-07");
  REQUIRE_NOTHROW( toyearmonthday(date) );
}

TEST_CASE("To year month day YEAR", "[toyearmonthday]") {

  Date date = parsedate("2024");
  REQUIRE_THROWS( toyearmonthday(date) );
}

