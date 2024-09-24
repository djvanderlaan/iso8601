#ifndef iso8601_time_h
#define iso8601_time_h

#include <stdexcept>
#include <ostream>

namespace ISO8601 {

  class Timezone {
    public:
      bool localtime = true;
      int offset_hours = 0;
      int offset_minutes = 0;

      Timezone(bool local = true, int hours = 0, int minutes = 0) : 
          localtime(local), offset_hours{hours}, offset_minutes(minutes) {
        if (localtime) {
          if (offset_hours != 0 || offset_minutes != 0) {
            throw std::runtime_error("Local time should not have a offset.");
          }
        } else {
          if (offset_hours < -12 || offset_hours > 12)
            throw std::runtime_error("Invalid offset of time zone.");
          if (offset_minutes < 0 || offset_minutes >= 60)
            throw std::runtime_error("Invalid offset of time zone.");
          if ((offset_hours == -12 || offset_hours == 12) && (offset_minutes != 0))
            throw std::runtime_error("Invalid offset of time zone.");
        }
      }
  };


  class Time {
    public:
      Time(double h, bool hfrac, Timezone tz = {}) : 
          hour_{h}, hour_fractional_{hfrac}, 
          timezone_{tz} {
        validate();
      }

      void set_hour(double value, bool fractional) {
        if (value < 0.0 || value > 24) throw std::runtime_error("Invalid time.");
        if (fractional && (minutes_fractional_ || seconds_fractional_)) 
          throw std::runtime_error("Invalid time.");
        hour_ = value;
        hour_fractional_ = fractional;
      }

      double hour() const {
        return hour_;
      }

      bool hour_fractional() const {
        return hour_fractional_;
      }

      void set_minutes(double value, bool fractional) {
        if (hour_fractional_) throw std::runtime_error("Invalid time.");
        if (value < 0.0 || value >= 60) throw std::runtime_error("Invalid time.");
        if (hour_ == 24 && value != 0) throw std::runtime_error("Invalid time.");
        has_minutes_ = true;
        minutes_ = value;
        minutes_fractional_ = fractional;
      }

      bool has_minutes() const {
        return has_minutes_;
      }

      double minutes() const {
        if (!has_minutes_) throw std::runtime_error("Time does not have minutes.");
        return minutes_;
      }

      bool minutes_fractional() const {
        if (!has_minutes_) throw std::runtime_error("Time does not have minutes.");
        return minutes_fractional_;
      }

      void set_seconds(double value, bool fractional) {
        if (hour_fractional_) throw std::runtime_error("Invalid time.");
        if (minutes_fractional_) throw std::runtime_error("Invalid time.");
        if (!has_minutes_) throw std::runtime_error("Invalid time.");
        if (value < 0.0 || value >= 60) throw std::runtime_error("Invalid time.");
        if (hour_ == 24 && value != 0) throw std::runtime_error("Invalid time.");
        has_seconds_ = true;
        seconds_ = value;
        seconds_fractional_ = fractional;
      }

      bool has_seconds() const {
        return has_seconds_;
      }

      double seconds() const {
        if (!has_seconds_) throw std::runtime_error("Time does not have seconds.");
        return seconds_;
      }

      bool seconds_fractional() const {
        if (!has_seconds_) throw std::runtime_error("Time does not have seconds.");
        return seconds_fractional_;
      }

      void set_timezone(const Timezone& tz) {
        timezone_ = tz;
      }

      const Timezone& timezone() const {
        return timezone_;
      }


    private:

      void validate() {
        if (has_seconds_ && !has_minutes_) throw std::runtime_error("Invalid time.");
        if (!has_minutes_ && minutes_ != 0.0) throw std::runtime_error("Invalid time.");
        if (!has_seconds_ && seconds_ != 0.0) throw std::runtime_error("Invalid time.");
        if (hour_fractional_ && (has_minutes_ || has_seconds_))  throw std::runtime_error("Invalid time.");
        if (minutes_fractional_ && has_seconds_)  throw std::runtime_error("Invalid time.");
        // TODO: check is hour = 24 is allowed
        if (hour_ < 0.0 || hour_ > 24.0) throw std::runtime_error("Invalid time.");
        if (has_minutes_ && (minutes_ < 0.0 || minutes_ > 60.0)) throw std::runtime_error("Invalid time.");
        if (has_seconds_ && (seconds_ < 0.0 || seconds_ > 60.0)) throw std::runtime_error("Invalid time.");
      }
      
      // hour
      double hour_ = 0.0;
      bool   hour_fractional_ = false;
      // minutes; optional
      double minutes_ = 0.0;
      bool   minutes_fractional_ = false;
      bool   has_minutes_ = false;
      // seconds; optional
      double seconds_ = 0.0;
      bool   seconds_fractional_ = false;
      bool   has_seconds_ = false;
      // timezone
      Timezone timezone_;
  };


  Time make_standard(const Time& time, bool fill_missing = false);

  std::ostream& operator<<(std::ostream& stream, const Timezone& tz);
  std::ostream& operator<<(std::ostream& stream, const Time& time);

}

#endif

