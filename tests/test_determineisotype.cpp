
#include "catch_amalgamated.hpp"

#include "iso8601.h"

TEST_CASE("Detect ISO8601 type", "[determineisotype]") {

  REQUIRE( determineisotype("2011-12-23") == ISOType::Date );
  REQUIRE( determineisotype("20111223") == ISOType::Date );
  REQUIRE( determineisotype("2011") == ISOType::Date );
  REQUIRE( determineisotype("2011-12-23 12:34") == ISOType::DateTime );
  REQUIRE( determineisotype("2011-12-23T12:34") == ISOType::DateTime );
  REQUIRE( determineisotype("12:34") == ISOType::Time );
  REQUIRE( determineisotype("1234") == ISOType::Date );
  REQUIRE( determineisotype("T12:34") == ISOType::Time );
  REQUIRE( determineisotype("2011-12-23/2012012023") == ISOType::TimeInterval );
  REQUIRE( determineisotype("T12:30/T13:00") == ISOType::TimeInterval );
  REQUIRE( determineisotype("PH1/T13:00") == ISOType::TimeInterval );
  REQUIRE( determineisotype("T12:00/PH1") == ISOType::TimeInterval );
  REQUIRE( determineisotype("P10/PH1") == ISOType::TimeInterval );
  REQUIRE( determineisotype("PH1") == ISOType::Duration );
  REQUIRE( determineisotype("") == ISOType::Date );

}

