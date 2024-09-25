
#include "catch_amalgamated.hpp"

#include "iso8601.h"

using namespace ISO8601;

TEST_CASE("Detect ISO8601 type", "[determinetype]") {

  REQUIRE( determinetype("2011-12-23") == ISOType::Date );
  REQUIRE( determinetype("20111223") == ISOType::Date );
  REQUIRE( determinetype("2011") == ISOType::Date );
  REQUIRE( determinetype("2011-12-23 12:34") == ISOType::DateTime );
  REQUIRE( determinetype("2011-12-23T12:34") == ISOType::DateTime );
  REQUIRE( determinetype("12:34") == ISOType::Time );
  REQUIRE( determinetype("1234") == ISOType::Date );
  REQUIRE( determinetype("T12:34") == ISOType::Time );
  REQUIRE( determinetype("2011-12-23/2012012023") == ISOType::TimeInterval );
  REQUIRE( determinetype("T12:30/T13:00") == ISOType::TimeInterval );
  REQUIRE( determinetype("PH1/T13:00") == ISOType::TimeInterval );
  REQUIRE( determinetype("T12:00/PH1") == ISOType::TimeInterval );
  REQUIRE( determinetype("P10/PH1") == ISOType::TimeInterval );
  REQUIRE( determinetype("PH1") == ISOType::Duration );
  REQUIRE( determinetype("") == ISOType::Date );

}

