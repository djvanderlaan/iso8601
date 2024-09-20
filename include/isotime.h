#ifndef timeclass_h
#define timeclass_h

#include <stdexcept>
#include <ostream>

class ISOTimezone {
  public:
    bool localtime = true;
    int offset_hours = 0;
    int offset_minutes = 0;

    ISOTimezone(bool local = true, int hours = 0, int minutes = 0) : 
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


class ISOTime {
  public:
    ISOTime(double h, bool hfrac, ISOTimezone tz = {}) : 
        hour{h}, hour_fractional{hfrac}, 
        timezone{tz} {
      validate();
    }

    ISOTime(double h, bool hfrac, double m, bool mfrac, ISOTimezone tz = {}) : 
        hour{h}, hour_fractional{hfrac}, 
        minutes{m}, minutes_fractional{mfrac}, has_minutes{true}, 
        timezone{tz} {
      validate();
    }

    ISOTime(double h, bool hfrac, double m, bool mfrac, double s, bool sfrac, ISOTimezone tz = {}) : 
        hour{h}, hour_fractional{hfrac}, 
        minutes{m}, minutes_fractional{mfrac}, has_minutes{true}, 
        seconds{s}, seconds_fractional{sfrac}, has_seconds{true}, 
        timezone{tz} {
      validate();
    }

    ISOTime(double h, bool hfrac, double m, bool mfrac, bool hasm, double s, bool sfrac, bool hass, ISOTimezone tz = {}) : 
        hour{h}, hour_fractional{hfrac}, 
        minutes{m}, minutes_fractional{mfrac}, has_minutes{hasm}, 
        seconds{s}, seconds_fractional{sfrac}, has_seconds{hass}, 
        timezone{tz} {
      validate();
    }

    void set_minutes(double value, bool fractional) {
      if (hour_fractional) throw std::runtime_error("Invalid time.");
      if (value < 0.0 || value >= 60) throw std::runtime_error("Invalid time.");
      has_minutes = true;
      minutes = value;
      minutes_fractional = fractional;
    }

    void set_seconds(double value, bool fractional) {
      if (hour_fractional) throw std::runtime_error("Invalid time.");
      if (minutes_fractional) throw std::runtime_error("Invalid time.");
      if (!has_minutes) throw std::runtime_error("Invalid time.");
      if (value < 0.0 || value >= 60) throw std::runtime_error("Invalid time.");
      has_seconds = true;
      seconds = value;
      seconds_fractional = fractional;
    }

    void set_timezone(const ISOTimezone& tz) {
      timezone = tz;
    }


  private:

    void validate() {
      if (has_seconds && !has_minutes) throw std::runtime_error("Invalid time.");
      if (!has_minutes && minutes != 0.0) throw std::runtime_error("Invalid time.");
      if (!has_seconds && seconds != 0.0) throw std::runtime_error("Invalid time.");
      if (hour_fractional && (has_minutes || has_seconds))  throw std::runtime_error("Invalid time.");
      if (minutes_fractional && has_seconds)  throw std::runtime_error("Invalid time.");
      // TODO: check is hour = 24 is allowed
      if (hour < 0.0 || hour > 24.0) throw std::runtime_error("Invalid time.");
      if (has_minutes && (minutes < 0.0 || minutes > 60.0)) throw std::runtime_error("Invalid time.");
      if (has_seconds && (seconds < 0.0 || seconds > 60.0)) throw std::runtime_error("Invalid time.");
    }
    

  public:
    // hour
    double hour = 0.0;
    bool   hour_fractional = false;
    // minutes; optional
    double minutes = 0.0;
    bool   minutes_fractional = false;
    bool   has_minutes = false;
    // seconds; optional
    double seconds = 0.0;
    bool   seconds_fractional = false;
    bool   has_seconds = false;
    // timezone
    ISOTimezone timezone;
};


ISOTime make_standard(const ISOTime& time, bool fill_missing = false);

std::ostream& operator<<(std::ostream& stream, const ISOTimezone& tz);
std::ostream& operator<<(std::ostream& stream, const ISOTime& time);

#endif

