#include "iso8601_duration.h"
#include <iomanip>
#include <cmath>

#include <iostream>

namespace ISO8601 {

  inline bool nonset(const Duration& duration) {
    return !(duration.has_years() || duration.has_months() || 
        duration.has_days() || duration.has_hours() || duration.has_minutes() || 
        duration.has_seconds() || duration.has_weeks());
  }

  Duration removefractions(const Duration& duration, bool round_seconds, double month_precision) {
    Duration d{};
    // Round year and month
    double years = duration.has_years() ? duration.years() : 0.0;
    double months = duration.has_months() ? duration.months() : 0.0;
    bool months_fractional = duration.has_months() ? 
      duration.months_fractional() : true;
    if (duration.has_years() && duration.years_fractional()) {
      months = (years - std::floor(years))*12;
      years  = std::floor(years);
    }
    if (std::abs(months - std::round(months)) < month_precision) {
      months = std::round(months);
      months_fractional = false;
    }
    if (years > 0) d.set_years(years, false);
    if (months > 0) d.set_months(months, months_fractional);
    // Round days, hours, ...
    double days = duration.has_days() ? duration.days() : 0.0;
    double hours = duration.has_hours() ? duration.hours() : 0.0;
    double minutes = duration.has_minutes() ? duration.minutes() : 0.0;
    double seconds = duration.has_seconds() ? duration.seconds() : 0.0;
    bool seconds_fractional = duration.has_seconds() ? 
      duration.seconds_fractional() : !round_seconds;
    hours   += (days - std::floor(days))*24.0;
    days     = std::floor(days);
    minutes += (hours - std::floor(hours))*60.0;
    hours    = std::floor(hours);
    seconds += (minutes - std::floor(minutes))*60.0;
    minutes  = std::floor(minutes);
    if (round_seconds) seconds = round(seconds);
    if (days > 0) d.set_days(days, false);
    if (hours > 0) d.set_hours(hours, false);
    if (minutes > 0) d.set_minutes(minutes, false);
    if (seconds > 0) d.set_seconds(seconds, seconds_fractional);
    if (nonset(d)) d.set_seconds(0, false);
    return d;
  }

  Duration standardise(const Duration& duration) {
    /*const Duration d0 = removefractions(duration);
    DurationElement seconds = d0.seconds();
    DurationElement minutes = d0.minutes();
    DurationElement hours = d0.hours();
    DurationElement days = d0.days();
    DurationElement months = d0.months();
    DurationElement years = d0.years();
    if (months.has_value()) {
      double m = months.value();
      double ny = static_cast<int>(std::floor(m)) / 12;
      if (ny > 0) {
        m = m - ny*12;
        if (m > 0) months.value(m, months.fractional());
        ny = years.has_value() ? years.value() + ny : ny;
        years.value(ny, false);
      }
    }
    if (seconds.has_value()) {
      double sec = seconds.value();
      double nmin = static_cast<int>(std::floor(sec)) / 60;
      if (nmin > 0) {
        sec = sec - nmin*60;
        if (sec > 0) seconds.value(sec, seconds.fractional());
        nmin = minutes.has_value() ? minutes.value() + nmin : nmin;
        minutes.value(nmin, false);
      }
    }
    if (minutes.has_value()) {
      double min = minutes.value();
      double nh = static_cast<int>(std::floor(min)) / 60;
      std::cout << nh << "\n";
      if (nh > 0) {
        std::cout << "foo" << "\n";
        min = min - nh*60;
        std::cout << "min = " << min << "\n";
        minutes.value(min, minutes.fractional());
        //if (min > 0) minutes.value(min, minutes.fractional()); else minutes.unset();
        std::cout << "m.v = " << minutes.value() << "\n";
        nh = hours.has_value() ? hours.value() + nh : nh;
        std::cout << "hh=" << nh << "\n";
        hours.value(nh, false);
        std::cout << "h.v = " << hours.value() << "\n";
      }
    }
    if (hours.has_value()) {
      double h = hours.value();
      double nd = static_cast<int>(std::floor(h)) / 24;
      if (nd > 0) {
        h = h - nd*24;
        if (h > 0) hours.value(h, hours.fractional());
        nd = days.has_value() ? days.value() + nd : nd;
        days.value(nd, false);
      }
    }*/
    Duration d;
    /*if (years.has_value()) d.years(years.value(), years.fractional());
    if (months.has_value()) d.months(months.value(), months.fractional());
    if (days.has_value()) d.days(days.value(), days.fractional());
    if (hours.has_value()) d.hours(hours.value(), hours.fractional());
    if (minutes.has_value()) d.minutes(minutes.value(), minutes.fractional());
    if (seconds.has_value()) d.seconds(seconds.value(), seconds.fractional());*/
    return d;
  }


  std::ostream& operator<<(std::ostream& stream, const Duration& duration) {
    bool hastime = duration.has_hours() || 
      duration.has_minutes() || duration.has_seconds();
    bool hasdate = duration.has_years() || duration.has_months() || 
      duration.has_days() || duration.has_weeks();
    stream << 'P';
    if (duration.has_years()) stream << duration.years() << 'Y';
    if (duration.has_months()) stream << duration.months() << 'M';
    if (duration.has_days()) stream << duration.days() << 'D';
    if (duration.has_weeks()) stream << duration.weeks() << 'W';
    if (hastime) {
      stream << 'T';
      if (duration.has_hours()) stream << duration.hours() << 'H';
      if (duration.has_minutes()) stream << duration.minutes() << 'M';
      if (duration.has_seconds()) stream << duration.seconds() << 'S';
    }
    // We omit values of 0 and elements that aren't set. But that could mean we
    // haven't printed anything except the 'P' which is invalid. Print a
    // duration of 0 seconds in that case.
    if (!hasdate && !hastime) stream << "T0S";
    return stream;
  }

}
