#ifndef iso8601_duration_h
#define iso8601_duration_h

#include <stdexcept>
#include <cmath>
#include <ostream>

namespace ISO8601 {


  class Duration {
    public:

      void set_years(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // check if lower parts are already set; if so error
        if (has_weeks_ || has_years_ || has_months_ || 
            has_days_ || has_hours_ || has_minutes_ || 
            has_seconds_) 
          throw std::runtime_error("Invalid duration.");
        if (!fractional) value = std::round(value);
        years_ = value;
        years_fractional_ = fractional;
        has_years_ = true;
      }

      bool has_years() const {
        return has_years_;
      }

      bool years_fractional() const {
        if (!has_years_) throw std::runtime_error("Years not set.");
        return years_fractional_;
      }

      double years() const {
        if (!has_years_) throw std::runtime_error("Years not set.");
        return years_;
      }

      void set_months(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // check if lower parts are already set; if so error
        if (has_weeks_ || has_months_ || has_days_ || 
            has_hours_ || has_minutes_ || has_seconds_) 
          throw std::runtime_error("Invalid duration.");
        // check if higher parts are fractional
        if (has_years_ && years_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (!fractional) value = std::round(value);
        months_ = value;
        months_fractional_ = fractional;
        has_months_ = true;
      }

      bool has_months() const {
        return has_months_;
      }

      bool months_fractional() const {
        if (!has_months_) throw std::runtime_error("Months not set.");
        return months_fractional_;
      }

      double months() const {
        if (!has_months_) throw std::runtime_error("Months not set.");
        return months_;
      }

      void set_days(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // check if lower parts are already set; if so error
        if (has_weeks_ || has_days_ || has_hours_ || 
            has_minutes_ || has_seconds_) 
          throw std::runtime_error("Invalid duration.");
        // check if higher parts are fractional
        if (has_years_ && years_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (has_months_ && months_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (!fractional) value = std::round(value);
        days_ = value;
        days_fractional_ = fractional;
        has_days_ = true;
      }

      bool has_days() const {
        return has_days_;
      }

      bool days_fractional() const {
        if (!has_days_) throw std::runtime_error("Days not set.");
        return days_fractional_;
      }

      double days() const {
        if (!has_days_) throw std::runtime_error("Days not set.");
        return days_;
      }

      void set_hours(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // check if lower parts are already set; if so error
        if (has_weeks_ || has_hours_ || has_minutes_ || has_seconds_) 
          throw std::runtime_error("Invalid duration.");
        // check if higher parts are fractional
        if (has_years_ && years_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (has_months_ && months_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (has_days_ && days_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (!fractional) value = std::round(value);
        hours_ = value;
        hours_fractional_ = fractional;
        has_hours_ = true;
      }

      bool has_hours() const {
        return has_hours_;
      }

      bool hours_fractional() const {
        if (!has_hours_) throw std::runtime_error("Hours not set.");
        return hours_fractional_;
      }

      double hours() const {
        if (!has_hours_) throw std::runtime_error("Hours not set.");
        return hours_;
      }

      void set_minutes(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // check if lower parts are already set; if so error
        if (has_weeks_ || has_minutes_ || has_seconds_) 
          throw std::runtime_error("Invalid duration.");
        // check if higher parts are fractional
        if (has_years_ && years_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (has_months_ && months_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (has_days_ && days_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (has_hours_ && hours_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (!fractional) value = std::round(value);
        minutes_ = value;
        minutes_fractional_ = fractional;
        has_minutes_ = true;
      }

      bool has_minutes() const {
        return has_minutes_;
      }

      bool minutes_fractional() const {
        if (!has_minutes_) throw std::runtime_error("Minutes not set.");
        return minutes_fractional_;
      }

      double minutes() const {
        if (!has_minutes_) throw std::runtime_error("Minutes not set.");
        return minutes_;
      }

      void set_seconds(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // check if lower parts are already set; if so error
        if (has_weeks_ || has_seconds_) 
          throw std::runtime_error("Invalid duration.");
        // check if higher parts are fractional
        if (has_years_ && years_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (has_months_ && months_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (has_days_ && days_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (has_hours_ && hours_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (has_minutes_ && minutes_fractional_) 
          throw std::runtime_error("Invalid duration.");
        if (!fractional) value = std::round(value);
        seconds_ = value;
        seconds_fractional_ = fractional;
        has_seconds_ = true;
      }

      bool has_seconds() const {
        return has_seconds_;
      }

      bool seconds_fractional() const {
        if (!has_seconds_) throw std::runtime_error("Seconds not set.");
        return seconds_fractional_;
      }

      double seconds() const {
        if (!has_seconds_) throw std::runtime_error("Seconds not set.");
        return seconds_;
      }

      void set_weeks(double value, bool fractional = false) {
        weeks(value, fractional);
      }

      void weeks(double value, bool fractional = false) {
        if (value < 0) throw std::runtime_error("Invalid duration.");
        // week cannot be combined with other types such as years, days etc.
        if (has_years_ || has_months_ || has_days_ || 
            has_hours_ || has_minutes_ || has_seconds_) 
          throw std::runtime_error("Invalid duration.");
        weeks_ = value;
        weeks_fractional_ = fractional;
        has_weeks_ = true;
      }

      bool has_weeks() const {
        return has_weeks_;
      }

      bool weeks_fractional() const {
        if (!has_weeks_) throw std::runtime_error("Weeks not set.");
        return weeks_fractional_;
      }

      double weeks() const {
        if (!has_weeks_) throw std::runtime_error("Weeks not set.");
        return weeks_;
      }

    private:
      bool has_years_ = false;
      double years_ = 0.0;
      bool years_fractional_ = false;

      bool has_months_ = false;
      double months_ = 0.0;
      bool months_fractional_ = false;

      bool has_days_ = false;
      double days_ = 0.0;
      bool days_fractional_ = false;

      bool has_hours_ = false;
      double hours_ = 0.0;
      bool hours_fractional_ = false;

      bool has_minutes_ = false;
      double minutes_ = 0.0;
      bool minutes_fractional_ = false;

      bool has_seconds_ = false;
      double seconds_ = 0.0;
      bool seconds_fractional_ = false;

      bool has_weeks_ = false;
      double weeks_ = 0.0;
      bool weeks_fractional_ = false;

  };


  std::ostream& operator<<(std::ostream& stream, const Duration& duration);

  Duration removefractions(const Duration& duration, bool round_seconds = false, 
      double month_precision = 0.01);
  Duration standardise(const Duration& duration);

}

#endif

