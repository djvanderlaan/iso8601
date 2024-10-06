
#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("To year week day YEARMONTHDAY", "[toyearweekday]") {

  Date date = parsedate("2023-01-01");
  Date date2 = toyearweekday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARWEEKDAY);
  REQUIRE(date2.year() == 2022);
  REQUIRE(date2.week() == 52);
  REQUIRE(date2.weekday() == 7);

  date = parsedate("2024-01-01");
  date2 = toyearweekday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARWEEKDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.week() == 1);
  REQUIRE(date2.weekday() == 1);

  date = parsedate("2024-10-06");
  date2 = toyearweekday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARWEEKDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.week() == 40);
  REQUIRE(date2.weekday() == 7);

  date = parsedate("2024-12-31");
  date2 = toyearweekday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARWEEKDAY);
  REQUIRE(date2.year() == 2025);
  REQUIRE(date2.week() == 1);
  REQUIRE(date2.weekday() == 2);

  date = parsedate("2023-12-31");
  date2 = toyearweekday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARWEEKDAY);
  REQUIRE(date2.year() == 2023);
  REQUIRE(date2.week() == 52);
  REQUIRE(date2.weekday() == 7);

  date = parsedate("2024-12");
  REQUIRE_THROWS( toyearweekday(date) );
}


TEST_CASE("To year week day YEARWEEKDAY", "[toyearweekday]") {

  Date date = parsedate("2024-W41-4");
  Date date2 = toyearweekday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARWEEKDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.week() == 41);
  REQUIRE(date2.weekday() == 4);
}

TEST_CASE("To year day YEARMONTHDAY", "[toyearweekday]") {

  Date date = parsedate("2023-001");
  Date date2 = toyearweekday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARWEEKDAY);
  REQUIRE(date2.year() == 2022);
  REQUIRE(date2.week() == 52);
  REQUIRE(date2.weekday() == 7);

  date = parsedate("2024-001");
  date2 = toyearweekday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARWEEKDAY);
  REQUIRE(date2.year() == 2024);
  REQUIRE(date2.week() == 1);
  REQUIRE(date2.weekday() == 1);

  date = parsedate("2024-366");
  date2 = toyearweekday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARWEEKDAY);
  REQUIRE(date2.year() == 2025);
  REQUIRE(date2.week() == 1);
  REQUIRE(date2.weekday() == 2);

  date = parsedate("2023-365");
  date2 = toyearweekday(date);
  REQUIRE(date2.type() == ISO8601::Date::YEARWEEKDAY);
  REQUIRE(date2.year() == 2023);
  REQUIRE(date2.week() == 52);
  REQUIRE(date2.weekday() == 7);

}

