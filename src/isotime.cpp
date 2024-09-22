#include "isotime.h"
#include <iomanip>
#include <cmath>

ISOTime make_standard(const ISOTime& time, bool fill_missing) {
  ISOTime t = time;
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
  if (fill_missing && !t.has_minutes()) {
    t.set_minutes(0, false);
  }
  if (t.has_minutes() && t.seconds_fractional()) {
    // check if seconds are practically integer
    const double sround = std::round(t.seconds());
    if (std::abs(t.seconds() - sround) < 1E-10) {
      t.set_seconds(sround, false);
    }
  }
  if (fill_missing && !t.has_seconds()) {
    t.set_seconds(0, false);
  }
  return t;
}

std::ostream& operator<<(std::ostream& stream, const ISOTimezone& tz) {
  if (tz.localtime) {
    // do nothing
  } else if (tz.offset_hours == 0 && tz.offset_minutes == 0) {
    stream << 'Z';
  } else {
    if (tz.offset_hours < 0) stream << '-'; else stream << '+';
    stream << std::setw(2) << std::setfill('0') << std::abs(tz.offset_hours);
    stream << ':' << std::setw(2) << std::setfill('0') << tz.offset_minutes;
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const ISOTime& time) {
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

