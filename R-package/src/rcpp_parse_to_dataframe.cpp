#include <Rcpp.h>
#include "iso8601.h"

using namespace Rcpp;


// A thin wrapper around a Rcpp::NumericVector. The vector is initiliased to a
// size of 0; as soon as it is assigned to it creates a full size vector. 
class NumVec {
  public:
    NumVec(R_xlen_t size) : len_(size), x_(0) {
    }

    double& operator[](R_xlen_t i) {
      if (x_.size() == 0) x_ = Rcpp::NumericVector(len_, NA_REAL);
      return x_[i];
    }

    Rcpp::NumericVector& vec() { return x_;}

  private:
    R_xlen_t len_;
    Rcpp::NumericVector x_;
};

// A thin wrapper around a Rcpp::IntegerVector. The vector is initiliased to a
// size of 0; as soon as it is assigned to it creates a full size vector. 
class IntVec {
  public:
    IntVec(R_xlen_t size) : len_(size), x_(0) {
    }

    int& operator[](R_xlen_t i) {
      if (x_.size() == 0) x_ = Rcpp::IntegerVector(len_, NA_INTEGER);
      return x_[i];
    }

    Rcpp::IntegerVector& vec() { return x_;}

  private:
    R_xlen_t len_;
    Rcpp::IntegerVector x_;
};

// [[Rcpp::export]]
List rcpp_parse_iso_dateframe(CharacterVector in_str, int transformdate = 0) {
  // We use IntVec and NumVec here. In that way we only create vectors that are
  // needed. For example, most times week and weekday will not be used and it
  // would be wastefull to create the full size vectors. In this case only
  // vectors of size 0 are created.
  IntegerVector isotype(in_str.size(), NA_INTEGER);
  IntVec year(in_str.size());
  IntVec month(in_str.size());
  IntVec day(in_str.size());
  IntVec week(in_str.size());
  IntVec weekday(in_str.size());
  IntVec yearday(in_str.size());
  NumVec hour(in_str.size());
  NumVec minutes(in_str.size());
  NumVec seconds(in_str.size());
  IntVec tzoffsethours(in_str.size());
  IntVec tzoffsetminutes(in_str.size());

  for (R_xlen_t i = 0, iend = in_str.size(); i < iend; ++i) {
    if (!CharacterVector::is_na(in_str[i])) {
      const std::string_view str{in_str[i]};
      ISO8601::ISO8601Type type = ISO8601::determinetype(str);
      try {

        switch (type) {
          case ISO8601::ISO8601Type::Date: {
              isotype[i] = 1;
              ISO8601::Date d = ISO8601::parsedate(str);
              if (transformdate != 0) {
                if (transformdate == 1) {
                  d = ISO8601::fillmissing(d);
                  d = ISO8601::toyearmonthday(d);
                } else if (transformdate == 2) {
                  d = ISO8601::fillmissing(d);
                  d = ISO8601::toyearday(d);
                } else {
                  throw std::runtime_error("Invalid value for transformdate.");
                }
              }
              year[i] = d.year();
              if (d.has_month()) month[i] = d.month();
              if (d.has_day()) day[i] = d.day();
              if (d.has_week()) week[i] = d.week();
              if (d.has_weekday()) weekday[i] = d.weekday();
              if (d.has_yearday()) yearday[i] = d.yearday();
            }
            break;
          case ISO8601::ISO8601Type::Time: {
              isotype[i] = 2;
              ISO8601::Time t = ISO8601::parsetime(str);
              hour[i] = t.hour();
              if (t.has_minutes()) minutes[i] = t.minutes();
              if (t.has_seconds()) seconds[i] = t.seconds();
              ISO8601::Timezone tz = t.timezone();
              if (!tz.localtime()) {
                tzoffsethours[i] = tz.offset_hours();
                tzoffsetminutes[i] = tz.offset_minutes();
              }
            }
            break;
          case ISO8601::ISO8601Type::Datetime: {
              isotype[i] = 3;
              ISO8601::Datetime dt = ISO8601::parsedatetime(str);
              ISO8601::Date d = dt.date();
              year[i] = d.year();
              if (d.has_month()) month[i] = d.month();
              if (d.has_day()) day[i] = d.day();
              if (d.has_week()) week[i] = d.week();
              if (d.has_weekday()) weekday[i] = d.weekday();
              if (d.has_yearday()) yearday[i] = d.yearday();
              ISO8601::Time t = dt.time();
              hour[i] = t.hour();
              if (t.has_minutes()) minutes[i] = t.minutes();
              if (t.has_seconds()) seconds[i] = t.seconds();
              ISO8601::Timezone tz = t.timezone();
              if (!tz.localtime()) {
                tzoffsethours[i] = tz.offset_hours();
                tzoffsetminutes[i] = tz.offset_minutes();
              }
            }
            break;
          case ISO8601::ISO8601Type::Duration:
            isotype[i] = 4;
            warning("Durations not yet supported. Returning NA.");
            break;
          case ISO8601::ISO8601Type::TimeInterval:
            isotype[i] = 5;
            warning("Time intervals not yet supported. Returning NA.");
            break;
          case ISO8601::ISO8601Type::RepeatingInterval:
            isotype[i] = 6;
            warning("Repeating intervals not yet supported. Returning NA.");
            break;
        }

      }
      catch (std::exception& e) {
        isotype[i] = NA_INTEGER;
        warning("Parsing of '%s' failed. Returning NA.", str);
      }
    }
  }

  return List::create(
    Named("type") = isotype,
    Named("year") = year.vec(),
    Named("month") = month.vec(),
    Named("day") = day.vec(),
    Named("week") = week.vec(),
    Named("weekday") = weekday.vec(),
    Named("yearday") = yearday.vec(),
    Named("hour") = hour.vec(),
    Named("minutes") = minutes.vec(),
    Named("seconds") = seconds.vec(),
    Named("tzoffsethours") = tzoffsethours.vec(),
    Named("tzoffsetminutes") = tzoffsetminutes.vec()
  );
}


