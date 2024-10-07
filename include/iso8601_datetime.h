#ifndef iso8601_datetime_h
#define iso8601_datetime_h

#include "iso8601_date.h"
#include "iso8601_time.h"
#include <ostream>

namespace ISO8601 {

  class Datetime {
    public:
      Datetime(const Date& date, const Time& time): date_{date}, time_{time} {
        if (date.type() == Date::YEAR || !iscomplete(date)) 
          throw std::runtime_error("Invalid ISO8601 datetime");
      }

      void date(const Date& date) {
        if (date.type() == Date::YEAR || !iscomplete(date)) 
          throw std::runtime_error("Invalid ISO8601 datetime");
        date_ = date;
      }

      const Date& date() const {
        return date_;
      }

      void time(const Time& time) {
        time_ = time;
      }

      const Time& time() const {
        return time_;
      }

    private:
      Date date_;
      Time time_;
  };

  std::ostream& operator<<(std::ostream& stream, const Datetime& datetime);

  Datetime tozulu(const Datetime& datetime);

  Datetime fillmissing(const Datetime& datetime);

}

#endif

