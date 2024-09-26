
#include "catch_amalgamated.hpp"

#include "iso8601.h"

using namespace ISO8601;

TEST_CASE("Detect ISO8601 type", "[determinetype]") {

  REQUIRE( determinetype("2011-12-23") == ISO8601Type::Date );
  REQUIRE( determinetype("20111223") == ISO8601Type::Date );
  REQUIRE( determinetype("2011") == ISO8601Type::Date );
  REQUIRE( determinetype("2011-12-23 12:34") == ISO8601Type::Datetime );
  REQUIRE( determinetype("2011-12-23T12:34") == ISO8601Type::Datetime );
  REQUIRE( determinetype("12:34") == ISO8601Type::Time );
  REQUIRE( determinetype("1234") == ISO8601Type::Date );
  REQUIRE( determinetype("T12:34") == ISO8601Type::Time );
  REQUIRE( determinetype("2011-12-23/2012012023") == ISO8601Type::TimeInterval );
  REQUIRE( determinetype("T12:30/T13:00") == ISO8601Type::TimeInterval );
  REQUIRE( determinetype("PH1/T13:00") == ISO8601Type::TimeInterval );
  REQUIRE( determinetype("T12:00/PH1") == ISO8601Type::TimeInterval );
  REQUIRE( determinetype("P10/PH1") == ISO8601Type::TimeInterval );
  REQUIRE( determinetype("PH1") == ISO8601Type::Duration );
  REQUIRE( determinetype("") == ISO8601Type::Date );

}

