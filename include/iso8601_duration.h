#ifndef iso8601_duration_h
#define iso8601_duration_h

#include <stdexcept>
#include <cmath>
#include <ostream>

namespace ISO8601 {

  class DurationElement {
    public:

      DurationElement() : value_{0.0}, fractional_{false}, has_value_{false} {}

      DurationElement(double value, bool fractional = false) : value_{value}, 
        fractional_{fractional}, has_value_{true} {}

      void value(double value, bool fractional = false) {
        value_ = value_;
        fractional_ = fractional_;
        has_value_ = true;
      }

      void unset() {
        has_value_ = false;
      }

      double has_value() const {
        return has_value_;
      }

      double value() const {
        if (!has_value_) throw std::runtime_error("Value not set.");
        return value_;
      }

      bool fractional() const {
        if (!has_value_) throw std::runtime_error("Value not set.");
        return fractional_;
      }

    private:
      double value_;
      bool fractional_;
      bool has_value_;
  };

  class Duration {
    public:

      void set_years(double value, bool fractional = false) {
        years(value, fractional);
      }

      void years(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // check if lower parts are already set; if so error
        if (weeks_.has_value() || years_.has_value() || months_.has_value() || 
            days_.has_value() || hours_.has_value() || minutes_.has_value() || 
            seconds_.has_value()) 
          throw std::runtime_error("Invalid duration.");
        if (!fractional) value = std::round(value);
        years_ = DurationElement{value, fractional};
      }

      bool has_years() const {
        return years_.has_value();
      }

      bool years_fractional() const {
        return years_.fractional();
      }

      double yearsv() const {
        return years_.value();
      }

      void set_months(double value, bool fractional = false) {
        months(value, fractional);
      }

      void months(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // check if lower parts are already set; if so error
        if (weeks_.has_value() || months_.has_value() || days_.has_value() || 
            hours_.has_value() || minutes_.has_value() || seconds_.has_value()) 
          throw std::runtime_error("Invalid duration.");
        // check if higher parts are fractional
        if (years_.has_value() && years_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (!fractional) value = std::round(value);
        months_ = DurationElement{value, fractional};
      }

      bool has_months() const {
        return months_.has_value();
      }

      bool months_fractional() const {
        return months_.fractional();
      }

      double monthsv() const {
        return months_.value();
      }

      void set_days(double value, bool fractional = false) {
        days(value, fractional);
      }

      void days(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // check if lower parts are already set; if so error
        if (weeks_.has_value() || days_.has_value() || hours_.has_value() || 
            minutes_.has_value() || seconds_.has_value()) 
          throw std::runtime_error("Invalid duration.");
        // check if higher parts are fractional
        if (years_.has_value() && years_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (months_.has_value() && months_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (!fractional) value = std::round(value);
        days_ = DurationElement{value, fractional};
      }

      bool has_days() const {
        return days_.has_value();
      }

      bool days_fractional() const {
        return days_.fractional();
      }

      double daysv() const {
        return days_.value();
      }

      void set_hours(double value, bool fractional = false) {
        hours(value, fractional);
      }

      void hours(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // check if lower parts are already set; if so error
        if (weeks_.has_value() || hours_.has_value() || minutes_.has_value() || 
            seconds_.has_value()) 
          throw std::runtime_error("Invalid duration.");
        // check if higher parts are fractional
        if (years_.has_value() && years_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (months_.has_value() && months_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (days_.has_value() && days_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (!fractional) value = std::round(value);
        hours_ = DurationElement{value, fractional};
      }

      bool has_hours() const {
        return hours_.has_value();
      }

      bool hours_fractional() const {
        return hours_.fractional();
      }

      double hoursv() const {
        return hours_.value();
      }

      void set_minutes(double value, bool fractional = false) {
        minutes(value, fractional);
      }

      void minutes(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // check if lower parts are already set; if so error
        if (weeks_.has_value() || minutes_.has_value() || seconds_.has_value()) 
          throw std::runtime_error("Invalid duration.");
        // check if higher parts are fractional
        if (years_.has_value() && years_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (months_.has_value() && months_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (days_.has_value() && days_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (hours_.has_value() && hours_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (!fractional) value = std::round(value);
        minutes_ = DurationElement{value, fractional};
      }

      bool has_minutes() const {
        return minutes_.has_value();
      }

      bool minutes_fractional() const {
        return minutes_.fractional();
      }

      double minutesv() const {
        return minutes_.value();
      }

      void set_seconds(double value, bool fractional = false) {
        seconds(value, fractional);
      }

      void seconds(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // check if lower parts are already set; if so error
        if (weeks_.has_value() || seconds_.has_value()) 
          throw std::runtime_error("Invalid duration.");
        // check if higher parts are fractional
        if (years_.has_value() && years_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (months_.has_value() && months_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (days_.has_value() && days_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (hours_.has_value() && hours_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (minutes_.has_value() && minutes_.fractional()) 
          throw std::runtime_error("Invalid duration.");
        if (!fractional) value = std::round(value);
        seconds_ = DurationElement{value, fractional};
      }

      bool has_seconds() const {
        return seconds_.has_value();
      }

      bool seconds_fractional() const {
        return seconds_.fractional();
      }

      double secondsv() const {
        return seconds_.value();
      }

      const DurationElement& seconds() const {
        return seconds_;
      }

      void set_weeks(double value, bool fractional = false) {
        weeks(value, fractional);
      }

      void weeks(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // week cannot be combined with other types such as years, days etc.
        if (years_.has_value() || months_.has_value() || days_.has_value() || 
            hours_.has_value() || minutes_.has_value() || seconds_.has_value()) 
          throw std::runtime_error("Invalid duration.");
        weeks_ = DurationElement{value, fractional};
      }

      bool has_weeks() const {
        return weeks_.has_value();
      }

      bool weeks_fractional() const {
        return weeks_.fractional();
      }

      double weeksv() const {
        return weeks_.value();
      }

    private:
      DurationElement years_ = {};
      DurationElement months_ = {};
      DurationElement days_ = {};
      DurationElement hours_ = {};
      DurationElement minutes_ = {};
      DurationElement seconds_ = {};
      DurationElement weeks_ = {};

  };


  std::ostream& operator<<(std::ostream& stream, const Duration& duration);

  Duration removefractions(const Duration& duration, bool round_seconds = false, 
      double month_precision = 0.01);
  Duration standardise(const Duration& duration);

}

#endif

