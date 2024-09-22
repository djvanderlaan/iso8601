
#include "catch_amalgamated.hpp"

#include "parsetime.h"

TEST_CASE("Time parsing THH:MM:SS", "[parsetime]") {
  ISOTime time = parsetime("T12:23:34");
  REQUIRE( time.hour == 12 );
}
