#include "iso8601_duration.h"
#include <iomanip>

namespace ISO8601 {


  bool printelement(std::ostream& stream, const DurationElement& el, char post) {
    if (el.has_value()) {// && el.value() > 0) {
      if (el.fractional()) {
        stream << el.value() << post;
      } else {
        stream << static_cast<int>(el.value()) << post;
      }
    } else return false;
    return true;
  }

  std::ostream& operator<<(std::ostream& stream, const Duration& duration) {
    bool hastime = duration.hours().has_value() || 
      duration.minutes().has_value() || duration.seconds().has_value();
    bool anythingprinted = false;
    stream << 'P';
    anythingprinted |= printelement(stream, duration.years(), 'Y');
    anythingprinted |= printelement(stream, duration.months(), 'M');
    anythingprinted |= printelement(stream, duration.days(), 'D');
    if (hastime) { 
      stream << 'T';
      anythingprinted |= printelement(stream, duration.hours(), 'H');
      anythingprinted |= printelement(stream, duration.minutes(), 'M');
      anythingprinted |= printelement(stream, duration.seconds(), 'S');
    }
    // We omit values of 0 and elements that aren't set. But that could mean we
    // haven't printed anything except the 'P' which is invalid. Print a
    // duration of 0 seconds in that case.
    if (!anythingprinted) stream << "0S";
    return stream;
  }

}
