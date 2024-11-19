#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("Duration parse P1Y2M3DT4H5M6,7S", "[parseduration]") {
  Duration d = parseduration("P1Y2M3DT4H5M6,7S");
  REQUIRE_FALSE(d.years().fractional());
  REQUIRE(d.years().value() == 1);
  REQUIRE_FALSE(d.months().fractional());
  REQUIRE(d.months().value() == 2);
  REQUIRE_FALSE(d.days().fractional());
  REQUIRE(d.days().value() == 3);
  REQUIRE_FALSE(d.hours().fractional());
  REQUIRE(d.hours().value() == 4);
  REQUIRE_FALSE(d.minutes().fractional());
  REQUIRE(d.minutes().value() == 5);
  REQUIRE(d.seconds().fractional());
  REQUIRE(d.seconds().value() == 6.7);
  REQUIRE_FALSE(d.weeks().has_value());
  REQUIRE_THROWS(d.weeks().value());
}

TEST_CASE("Duration parse PT4H5M6.7S", "[parseduration]") {
  Duration d = parseduration("PT4H5M6.7S");
  REQUIRE_FALSE(d.years().has_value());
  REQUIRE_FALSE(d.months().has_value());
  REQUIRE_FALSE(d.days().has_value());
  REQUIRE_FALSE(d.hours().fractional());
  REQUIRE(d.hours().value() == 4);
  REQUIRE_FALSE(d.minutes().fractional());
  REQUIRE(d.minutes().value() == 5);
  REQUIRE(d.seconds().fractional());
  REQUIRE(d.seconds().value() == 6.7);
  REQUIRE_THROWS(d.years().value());
  REQUIRE_THROWS(d.months().value());
  REQUIRE_THROWS(d.days().value());
  REQUIRE_FALSE(d.weeks().has_value());
  REQUIRE_THROWS(d.weeks().value());
}

TEST_CASE("Duration parse P01Y299M3,4D", "[parseduration]") {
  Duration d = parseduration("P01Y299M3.4D");
  REQUIRE_FALSE(d.years().fractional());
  REQUIRE(d.years().value() == 1);
  REQUIRE_FALSE(d.months().fractional());
  REQUIRE(d.months().value() == 299);
  REQUIRE(d.days().fractional());
  REQUIRE(d.days().value() == 3.4);
  REQUIRE_FALSE(d.hours().has_value());
  REQUIRE_FALSE(d.minutes().has_value());
  REQUIRE_FALSE(d.seconds().has_value());
  REQUIRE_THROWS(d.hours().value());
  REQUIRE_THROWS(d.minutes().value());
  REQUIRE_THROWS(d.seconds().value());
  REQUIRE_FALSE(d.weeks().has_value());
  REQUIRE_THROWS(d.weeks().value());
}

TEST_CASE("Duration parse P99.5W", "[parseduration]") {
  Duration d = parseduration("P99.5W");
  REQUIRE(d.weeks().fractional());
  REQUIRE(d.weeks().value() == 99.5);
  REQUIRE_FALSE(d.years().has_value());
  REQUIRE_FALSE(d.months().has_value());
  REQUIRE_FALSE(d.days().has_value());
  REQUIRE_THROWS(d.years().value());
  REQUIRE_THROWS(d.months().value());
  REQUIRE_THROWS(d.days().value());
  REQUIRE_FALSE(d.hours().has_value());
  REQUIRE_FALSE(d.minutes().has_value());
  REQUIRE_FALSE(d.seconds().has_value());
  REQUIRE_THROWS(d.hours().value());
  REQUIRE_THROWS(d.minutes().value());
  REQUIRE_THROWS(d.seconds().value());
}


TEST_CASE("Incorrect durations", "[parsedate]") {
  // wrong order
  REQUIRE_THROWS( parseduration("P2M1Y3DT4H5M6S") );
  REQUIRE_THROWS( parseduration("P1Y3D2MT4H5M6S") );
  REQUIRE_THROWS( parseduration("P1Y2M3DT4M5H6S") );
  REQUIRE_THROWS( parseduration("P1Y2M3DT4H5S6M") );
  // Repeat
  REQUIRE_THROWS( parseduration("P1Y2Y3DT4H5M6S") );
  REQUIRE_THROWS( parseduration("P1Y2M3DT4H5M6M") );
  // date in time and vice versa
  REQUIRE_THROWS( parseduration("P2M3DT4Y5M6S") );
  REQUIRE_THROWS( parseduration("P1Y2MT4H5D6S") );
  REQUIRE_THROWS( parseduration("P1H2M3DT5M6S") );
  REQUIRE_THROWS( parseduration("P1Y2M3ST4H5M") );
  // no T/P
  REQUIRE_THROWS( parseduration("P1Y2M3D4H5M6S") );
  REQUIRE_THROWS( parseduration("P4H5M6S") );
  REQUIRE_THROWS( parseduration("1Y2M3DT4H5M6S") );
  REQUIRE_THROWS( parseduration("P") );
  REQUIRE_THROWS( parseduration("P1") );
  // extra characters
  REQUIRE_THROWS( parseduration(" P1Y2M3DT4H5M6S") );
  REQUIRE_THROWS( parseduration("P1Y2M3DT4H5M6S ") );
  // fraction should be last
  REQUIRE_THROWS( parseduration("P1Y2M3DT4H5.5M6S") );
  REQUIRE_THROWS( parseduration("P1Y2M3DT4.5H5") );
  REQUIRE_THROWS( parseduration("P1Y2M3.5DT4H") );
  REQUIRE_THROWS( parseduration("P1Y2.5M3D") );
  REQUIRE_THROWS( parseduration("P1.4Y2.5M") );
  // weeks cannot be combined with anything else
  REQUIRE_THROWS( parseduration("P1Y99.5W") );
  REQUIRE_THROWS( parseduration("P1M99.5W") );
  REQUIRE_THROWS( parseduration("M99.5WT1H") );
  REQUIRE_THROWS( parseduration("M99.5WT1M") );
  REQUIRE_THROWS( parseduration("M99.5WT1S") );
  REQUIRE_THROWS( parseduration("M99.5WT") );
}


