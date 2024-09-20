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

std::ostream& operator<<(std::ostream& stream, const ISOTimezone& tz);

class ISOTime {
  public:
    int hour = 0;
    double hour_fractions = 0;
    bool has_minutes = false;
    int minutes = 0;
    double minute_fractions = 0;
    bool has_seconds = false;
    int seconds = 0;
    double second_fractions = 0;
    ISOTimezone timezone;
};


#endif

