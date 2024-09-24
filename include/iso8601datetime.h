#ifndef iso8601datetime_h
#define iso8601datetime_h

class ISO8601datetime {
  public:
    ISO8601datetime(const ISODate& date, const ISOTime& time): date_{date}, time_{time} {
      // Check if we have a full date
      switch (date.type()) {
        case ISODate::YEAR:
          throw std::runtime_error("Invalid ISO8601 datetime");
        case ISODate::YEARMONTHDAY:
          if (!date.has_month() || !date.has_day())
            throw std::runtime_error("Invalid ISO8601 datetime");
          break;
        case ISODate::YEARWEEKDAY:
          if (!date.has_week() || !date.has_weekday())
            throw std::runtime_error("Invalid ISO8601 datetime");
          break;
        case ISODate::YEARDAY:
          if (!date.has_yearday())
            throw std::runtime_error("Invalid ISO8601 datetime");
          break;
      }
    }

    const ISODate& date() const {
      return date_;
    }

    const ISOTime& time() const {
      return time_;
    }

  private:
    ISODate date_;
    ISOTime time_;
};

#endif

