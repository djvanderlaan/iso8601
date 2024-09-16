#ifndef time_h
#define time_h

#include<stdexcept>

class Timezone {
  public:
    bool localtime = true;
    int offset_hours = 0;
    int offset_minutes = 0;

    void set_zulu() {
      localtime = false;
      offset_hours = 0;
      offset_minutes = 0;
    }

    void set_local() {
      localtime = true;
      offset_hours = 0;
      offset_minutes = 0;
    }

    void set_offset_hours(int offset) {
      if (offset < -12 || offset > 12)
        throw std::runtime_error("Invalid offset of time zone.");
      if ((offset == -12 || offset == 12) && (offset_minutes != 0))
        throw std::runtime_error("Invalid offset of time zone.");
      offset_hours = offset;
      if (offset != 0) localtime = false;
    }

    void set_offset_minutes(int offset) {
      if (offset < 0 | offset >= 60)
        throw std::runtime_error("Invalid offset of time zone.");
      if ((offset_hours == -12 || offset_hours == 12) && (offset != 0))
        throw std::runtime_error("Invalid offset of time zone.");
      offset_minutes = offset;
      if (offset != 0) localtime = false;
    }
};

class Time {
  public:
    int hour = 0;
    double hour_fractions = 0;
    int minutes = 0;
    double minute_fractions = 0;
    int seconds = 0;
    double second_fractions = 0;
    Timezone timezone;
};


#endif
