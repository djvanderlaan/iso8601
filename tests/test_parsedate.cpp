
#include "catch_amalgamated.hpp"

#include "parsedate.h"

TEST_CASE("Date parsing yearmonthday", "[parsedate]") {
  ISODate date = parsedate("2022-12-12");

  REQUIRE( date.type() == ISODate::YEARMONTHDAY );
  REQUIRE( !date.has_month()  );

}

