#include "iso8601_duration.h"
#include <iomanip>
#include <cmath>

#include <iostream>

namespace ISO8601 {

  Duration removefractions(const Duration& duration, bool round_seconds, double month_precision) {
    Duration d{};
/*    // Round year and month
    if (duration.years().has_value() && duration.years().fractional()) {
      const double f = duration.years().value();
      d.years(std::floor(f), false);
      const double m = (f - d.years().value())*12;
      if (std::abs(m - std::round(m)) < month_precision) {
        if (std::round(m) > 0) d.months(std::round(m), false);
      } else {
        d.months(m, true);
      }
    } 
    if (!d.years().has_value() && duration.years().has_value()) 
      d.years(duration.years().value(), duration.years().fractional());
    if (!d.months().has_value() && duration.months().has_value()) 
      d.months(duration.months().value(), duration.months().fractional());
    // Round days
    if (duration.days().has_value() && duration.days().fractional()) {
      double remain = duration.days().value();
      if (std::floor(remain) > 0) d.days(std::floor(remain), false);
      remain = (remain - std::floor(remain)) * 24.0;
      if (std::floor(remain) > 0) d.hours(std::floor(remain), false);
      remain = (remain - std::floor(remain)) * 60.0;
      if (std::floor(remain) > 0) d.minutes(std::floor(remain), false);
      remain = (remain - std::floor(remain)) * 60.0;
      if (round_seconds) {
        if (std::round(remain) > 0) d.seconds(std::round(remain), false);
      } else {
        if (std::floor(remain) > 0) d.seconds(remain, true);
      }
    }
    if (!d.days().has_value() && duration.days().has_value()) 
      d.days(duration.days().value(), duration.days().fractional());
    // Round hours
    if (duration.hours().has_value() && duration.hours().fractional()) {
      double remain = duration.hours().value();
      if (std::floor(remain) > 0) d.hours(std::floor(remain), false);
      remain = (remain - std::floor(remain)) * 60.0;
      if (std::floor(remain) > 0) d.minutes(std::floor(remain), false);
      remain = (remain - std::floor(remain)) * 60.0;
      if (round_seconds) {
        if (std::round(remain) > 0) d.seconds(std::round(remain), false);
      } else {
        if (std::floor(remain) > 0) d.seconds(remain, true);
      }
    }
    if (!d.hours().has_value() && duration.hours().has_value()) 
      d.hours(duration.hours().value(), duration.hours().fractional());
    // Round minutes
    if (duration.minutes().has_value() && duration.minutes().fractional()) {
      double remain = duration.minutes().value();
      if (std::floor(remain) > 0) d.minutes(std::floor(remain), false);
      remain = (remain - std::floor(remain)) * 60.0;
      if (round_seconds) {
        if (std::round(remain) > 0) d.seconds(std::round(remain), false);
      } else {
        if (std::floor(remain) > 0) d.seconds(remain, true);
      }
    }
    if (!d.minutes().has_value() && duration.minutes().has_value()) 
      d.minutes(duration.minutes().value(), duration.minutes().fractional());
    // Round seconds
    if (duration.seconds().has_value()&& duration.seconds().fractional()) {
      double remain = duration.seconds().value();
      if (round_seconds) {
        if (std::round(remain) > 0) d.seconds(std::round(remain), false);
      } else {
        if (std::floor(remain) > 0) d.seconds(remain, true);
      }
    }
    if (!d.seconds().has_value() && duration.seconds().has_value()) 
      d.seconds(duration.seconds().value(), duration.seconds().fractional());*/
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
