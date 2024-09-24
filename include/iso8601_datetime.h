#ifndef iso8601_datetime_h
#define iso8601_datetime_h

#include "iso8601_date.h"
#include "iso8601_time.h"

namespace ISO8601 {

  class Datetime {
    public:
      Datetime(const Date& date, const Time& time): date_{date}, time_{time} {
        // Check if we have a full date
        switch (date.type()) {
          case Date::YEAR:
            throw std::runtime_error("Invalid ISO8601 datetime");
          case Date::YEARMONTHDAY:
            if (!date.has_month() || !date.has_day())
              throw std::runtime_error("Invalid ISO8601 datetime");
            break;
          case Date::YEARWEEKDAY:
            if (!date.has_week() || !date.has_weekday())
              throw std::runtime_error("Invalid ISO8601 datetime");
            break;
          case Date::YEARDAY:
            if (!date.has_yearday())
              throw std::runtime_error("Invalid ISO8601 datetime");
            break;
        }
      }

      const Date& date() const {
        return date_;
      }

      const Time& time() const {
        return time_;
      }

    private:
      Date date_;
      Time time_;
  };

}

#endif

