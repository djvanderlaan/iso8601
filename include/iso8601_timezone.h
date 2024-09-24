#ifndef iso8601_timezone_h
#define iso8601_timezone_h

#include <stdexcept>
#include <ostream>

namespace ISO8601 {

  class Timezone {
    public:
      Timezone(bool local = true, int hours = 0, int minutes = 0) : 
          localtime_{local}, offset_hours_{hours}, offset_minutes_{minutes} {
        if (localtime_) {
          if (offset_hours_ != 0 || offset_minutes_ != 0) {
            throw std::runtime_error("Local time should not have a offset.");
          }
        } else {
          if (offset_hours_ < -12 || offset_hours_ > 12)
            throw std::runtime_error("Invalid offset of time zone.");
          if (offset_minutes_ < 0 || offset_minutes_ >= 60)
            throw std::runtime_error("Invalid offset of time zone.");
          if ((offset_hours_ == -12 || offset_hours_ == 12) && (offset_minutes_ != 0))
            throw std::runtime_error("Invalid offset of time zone.");
        }
      }

      bool localtime() const {
        return localtime_;
      }

      int offset_hours() const {
        return offset_hours_;
      }

      int offset_minutes() const {
        return offset_minutes_;
      }

    private:
      bool localtime_ = true;
      int offset_hours_ = 0;
      int offset_minutes_ = 0;
  };


  std::ostream& operator<<(std::ostream& stream, const Timezone& tz);

}

#endif

