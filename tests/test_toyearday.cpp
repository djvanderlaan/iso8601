#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("To year day YEARMONTHDAY", "[toyearday]") {

  Date date = parsedate("2024-05-02");
  Date date2 = toyearday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.yearday() == 123);

  date = parsedate("2024-06-30");
  date2 = toyearday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.yearday() == 182);

  date = parsedate("2023-07-01");
  date2 = toyearday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARDAY);
  REQUIRE(date2.year() == 2023);
  REQUIRE(date2.yearday() == 182);

  date = parsedate("2023-07");
  REQUIRE_THROWS( toyearday(date) );
}

TEST_CASE("To year day YEARDAY", "[toyearday]") {

  Date date = parsedate("2024-123");
  Date date2 = toyearday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.yearday() == 123);
}

TEST_CASE("To year day YEARWEEKDAY", "[toyearday]") {

  Date date = parsedate("2024-W41-4");
  Date date2 = toyearday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.yearday() == 284);

  date = parsedate("2004-W41-7");
  date2 = toyearday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARDAY);
  REQUIRE(date2.year() == 2004);
  REQUIRE(date2.yearday() == 284);

  date = parsedate("2024-W01-1");
  date2 = toyearday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.yearday() == 1);

  date = parsedate("2025-W01-1");
  date2 = toyearday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.yearday() == 365);

  date = parsedate("2023-W01-1");
  date2 = toyearday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARDAY);
  REQUIRE(date2.year() == 2023);
  REQUIRE(date2.yearday() == 2);

  date = parsedate("2023-W01");
  REQUIRE_THROWS( toyearday(date) );
}

