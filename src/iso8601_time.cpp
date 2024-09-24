#include "iso8601_time.h"
#include <iomanip>
#include <cmath>


namespace ISO8601 {

  Time remove_fractions(const Time& time, bool round_seconds) {
    Time t = time;
    if (t.hour_fractional()) {
      const double hf = t.hour();
      t.set_hour(std::floor(t.hour()), false);
      t.set_minutes((hf - t.hour())*60.0, true);
    } 
    if (t.has_minutes() && t.minutes_fractional()) {
      const double mf = t.minutes();
      t.set_minutes(floor(mf), false);
      t.set_seconds((mf - t.minutes())*60.0, true);
    }
    if (t.has_seconds() && t.seconds_fractional()) {
      // check if seconds are practically integer
      const double sround = std::round(t.seconds());
      if (round_seconds || std::abs(t.seconds() - sround) < 1E-10) {
        t.set_seconds(std::round(sround), false);
      }
    }
    return t;
  }

  Time fill_missing(const Time& time) {
    Time t = time;
    if (time.hour_fractional() || (time.has_minutes() && time.minutes_fractional())) {
      t = remove_fractions(time);
    }
    if (!t.has_minutes()) {
      t.set_minutes(0, false);
    }
    if (!t.has_seconds()) {
      t.set_seconds(0, false);
    }
    return t;
  }

  std::ostream& operator<<(std::ostream& stream, const Time& time) {
    stream << 'T';
    if (time.hour_fractional()) {
      if (time.hour() < 10) stream << '0';
      stream << time.hour();
    } else {
      stream << std::setw(2) << std::setfill('0') << static_cast<int>(std::round(time.hour()));
    }
    if (time.has_minutes()) {
      stream << ':';
      if (time.minutes_fractional()) {
        if (time.minutes() < 10) stream << '0';
        stream << time.minutes();
      } else {
        stream << std::setw(2) << std::setfill('0') << static_cast<int>(std::round(time.minutes()));
      }
    }
    if (time.has_seconds()) {
      stream << ':';
      if (time.seconds_fractional()) {
        if (time.seconds() < 10) stream << '0';
        stream << time.seconds();
      } else {
        stream << std::setw(2) << std::setfill('0') << static_cast<int>(std::round(time.seconds()));
      }
    }
    stream << time.timezone();
    return stream;
  }

}

