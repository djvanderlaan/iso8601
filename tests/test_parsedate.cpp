
#include "catch_amalgamated.hpp"

#include "iso8601.h"
using namespace ISO8601;

TEST_CASE("Date parsing YYYY", "[parsedate]") {
  Date date = parsedate("2022");
  REQUIRE( date.type() == Date::YEAR );
  REQUIRE( date.year() == 2022 );
  REQUIRE_FALSE( date.has_month()  );
  REQUIRE_THROWS( date.month() == 12 );
  REQUIRE_FALSE( date.has_day()  );
  REQUIRE_THROWS( date.day() == 22 );
  REQUIRE_FALSE( date.has_week() );
  REQUIRE_THROWS( date.week() ); 
  REQUIRE_FALSE( date.has_weekday() );
  REQUIRE_THROWS( date.weekday() ); 
  REQUIRE_FALSE( date.has_yearday() );
  REQUIRE_THROWS( date.yearday() ); 
}
  
TEST_CASE("Date parsing -YYYY", "[parsedate]") {
  Date date = parsedate("-2022");
  REQUIRE( date.type() == Date::YEAR );
  REQUIRE( date.year() == -2022 );
}

TEST_CASE("Date parsing −YYYY", "[parsedate]") {
  // this is unicode minus not hyphen
  Date date = parsedate("−2022");
  REQUIRE( date.type() == Date::YEAR );
  REQUIRE( date.year() == -2022 );
}
  
  
TEST_CASE("Date parsing +YYYY", "[parsedate]") {
  Date date = parsedate("+2022");
  REQUIRE( date.type() == Date::YEAR );
  REQUIRE( date.year() == 2022 );
}

TEST_CASE("Date parsing YYYY-MM-DD", "[parsedate]") {
  Date date = parsedate("2022-12-22");
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 12 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 22 );
  REQUIRE_FALSE( date.has_week() );
  REQUIRE_THROWS( date.week() ); 
  REQUIRE_FALSE( date.has_weekday() );
  REQUIRE_THROWS( date.weekday() ); 
  REQUIRE_FALSE( date.has_yearday() );
  REQUIRE_THROWS( date.yearday() ); 
}
  
TEST_CASE("Date parsing YYYYMMDD", "[parsedate]") {
  Date date = parsedate("20221222");
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 12 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 22 );
}

TEST_CASE("Date parsing YYYY-MM", "[parsedate]") {
  Date date = parsedate("2022-12");
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 12 );
  REQUIRE_FALSE( date.has_day()  );
  REQUIRE_THROWS( date.day() );
}

TEST_CASE("Date parsing -YYYYMMDD", "[parsedate]") {
  Date date = parsedate("-20221222");
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == -2022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 12 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 22 );
}

TEST_CASE("Date parsing invalid dates YYYY-MM-DD", "[parsedate]") {
  REQUIRE_THROWS( parsedate("202212") );
  REQUIRE_THROWS( parsedate("2022-1222") );
  REQUIRE_THROWS( parsedate("202212-22") );
  REQUIRE_THROWS( parsedate("2022-13-22") );
  REQUIRE_THROWS( parsedate("2022-00-22") );
  REQUIRE_THROWS( parsedate("2022-12-32") );
  REQUIRE_THROWS( parsedate("2022-12-00") );
  REQUIRE_THROWS( parsedate("2022-12-1") );
  REQUIRE_THROWS( parsedate("222-12-32") );
  REQUIRE_THROWS( parsedate("2022-12-") );
  REQUIRE_THROWS( parsedate("2022-12-01 ") );
  REQUIRE_THROWS( parsedate(" 2022-12-01") );
  REQUIRE_THROWS( parsedate("2022-12 ") );
}

TEST_CASE("Date parsing YYYY-DDD", "[parsedate]") {
  Date date = parsedate("2022-123");
  REQUIRE( date.type() == Date::YEARDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_yearday() );
  REQUIRE( date.yearday() == 123); 
  REQUIRE_FALSE( date.has_month()  );
  REQUIRE_THROWS( date.month() == 12 );
  REQUIRE_FALSE( date.has_day()  );
  REQUIRE_THROWS( date.day() == 22 );
  REQUIRE_FALSE( date.has_week() );
  REQUIRE_THROWS( date.week() ); 
  REQUIRE_FALSE( date.has_weekday() );
  REQUIRE_THROWS( date.weekday() ); 
}

TEST_CASE("Date parsing −YYYY-DDD", "[parsedate]") {
  // this is unicode minus not hyphen
  Date date = parsedate("−2022-123");
  REQUIRE( date.type() == Date::YEARDAY );
  REQUIRE( date.year() == -2022 );
  REQUIRE( date.has_yearday() );
  REQUIRE( date.yearday() == 123); 
  REQUIRE_FALSE( date.has_month()  );
  REQUIRE_THROWS( date.month() == 12 );
  REQUIRE_FALSE( date.has_day()  );
  REQUIRE_THROWS( date.day() == 22 );
  REQUIRE_FALSE( date.has_week() );
  REQUIRE_THROWS( date.week() ); 
  REQUIRE_FALSE( date.has_weekday() );
  REQUIRE_THROWS( date.weekday() ); 
}
  
  
TEST_CASE("Date parsing YYYYDDD", "[parsedate]") {
  Date date = parsedate("2022123");
  REQUIRE( date.type() == Date::YEARDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_yearday() );
  REQUIRE( date.yearday() == 123); 
}

TEST_CASE("Date parsing invalid dates YYYY-DDD", "[parsedate]") {
  REQUIRE_THROWS( parsedate("2022-000") );
  REQUIRE_THROWS( parsedate("2022-366") );
  REQUIRE_NOTHROW( parsedate("2024-366") );
  REQUIRE_THROWS( parsedate("2022-367") );
  REQUIRE_THROWS( parsedate("2022-123-") );
  REQUIRE_THROWS( parsedate("2022-123 ") );
}
  
TEST_CASE("Date parsing YYYY-Www-D", "[parsedate]") {
  Date date = parsedate("2022-W12-3");
  REQUIRE( date.type() == Date::YEARWEEKDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_week() );
  REQUIRE( date.week() == 12); 
  REQUIRE( date.has_weekday() );
  REQUIRE( date.weekday() == 3); 
  REQUIRE_FALSE( date.has_month()  );
  REQUIRE_THROWS( date.month() == 12 );
  REQUIRE_FALSE( date.has_day()  );
  REQUIRE_THROWS( date.day() == 22 );
  REQUIRE_FALSE( date.has_yearday() );
  REQUIRE_THROWS( date.yearday() == 123); 
}
  
TEST_CASE("Date parsing YYYYWwwD", "[parsedate]") {
  Date date = parsedate("2022W123");
  REQUIRE( date.type() == Date::YEARWEEKDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_week() );
  REQUIRE( date.week() == 12); 
  REQUIRE( date.has_weekday() );
  REQUIRE( date.weekday() == 3); 
}
  
TEST_CASE("Date parsing YYYYWww", "[parsedate]") {
  Date date = parsedate("2022W12");
  REQUIRE( date.type() == Date::YEARWEEKDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_week() );
  REQUIRE( date.week() == 12); 
  REQUIRE_FALSE( date.has_weekday() );
  REQUIRE_THROWS( date.weekday()); 
}

TEST_CASE("Date parsing YYYY-Www", "[parsedate]") {
  Date date = parsedate("2022W12");
  REQUIRE( date.type() == Date::YEARWEEKDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_week() );
  REQUIRE( date.week() == 12); 
  REQUIRE_FALSE( date.has_weekday() );
  REQUIRE_THROWS( date.weekday()); 
}

TEST_CASE("Date parsing +YYYYYY-MM-DD", "[parsedate]") {
  Date date = parsedate("+002022-12-22", 2U);
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == 2022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 12 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 22 );
  REQUIRE_FALSE( date.has_week() );
  REQUIRE_THROWS( date.week() ); 
  REQUIRE_FALSE( date.has_weekday() );
  REQUIRE_THROWS( date.weekday() ); 
  REQUIRE_FALSE( date.has_yearday() );
  REQUIRE_THROWS( date.yearday() ); 
}

TEST_CASE("Date parsing -YYYYYY-MM-DD", "[parsedate]") {
  Date date = parsedate("-102022-12-22", 2U);
  REQUIRE( date.type() == Date::YEARMONTHDAY );
  REQUIRE( date.year() == -102022 );
  REQUIRE( date.has_month()  );
  REQUIRE( date.month() == 12 );
  REQUIRE( date.has_day()  );
  REQUIRE( date.day() == 22 );
  REQUIRE_FALSE( date.has_week() );
  REQUIRE_THROWS( date.week() ); 
  REQUIRE_FALSE( date.has_weekday() );
  REQUIRE_THROWS( date.weekday() ); 
  REQUIRE_FALSE( date.has_yearday() );
  REQUIRE_THROWS( date.yearday() ); 
}


TEST_CASE("Date parsing invalid dates", "[parsedate]") {
  REQUIRE_THROWS( parsedate("2022-W123") );
  REQUIRE_THROWS( parsedate("2022-W54-3") );
  REQUIRE_THROWS( parsedate("2022-W00-3") );
  REQUIRE_THROWS( parsedate("2022-W12-0") );
  REQUIRE_THROWS( parsedate("2022-W12-8") );
  REQUIRE_THROWS( parsedate("2022-W12-") );
  REQUIRE_THROWS( parsedate("002022-12-22", 2U) );
  REQUIRE_THROWS( parsedate("-002022-12-22", 3U) );
}


