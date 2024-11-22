#include "iso8601_duration.h"
#include "utils.h"
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
    // Weeks
    if (duration.has_weeks() && !duration.weeks_fractional()) 
      d.set_weeks(duration.weeks(), false);
    // else we convert weeks to days; cannot have week and days
    // Round days, hours, ...
    double days = duration.has_days() ? duration.days() : 0.0;
    if (duration.has_weeks() && duration.weeks_fractional()) 
      days += duration.weeks()*7.0;
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
    const Duration d0 = removefractions(duration);
    Duration d{};
    // Handle months and years
    double years = d0.has_years() ? d0.years() : 0.0;
    double months = d0.has_months() ? d0.months() : 0.0;
    const int nyears = static_cast<int>(std::floor(months))/12;
    years += nyears;
    months -= nyears * 12;
    if (years > 0) 
      d.set_years(years, d0.has_years() && d0.years_fractional());
    if (months > 0) 
      d.set_months(months, d0.has_months() && d0.months_fractional());
    // Handle days, hours, minutes, seconds
    double days = d0.has_days() ? d0.days() : 0.0;
    double hours = d0.has_hours() ? d0.hours() : 0.0;
    double minutes = d0.has_minutes() ? d0.minutes() : 0.0;
    double seconds = d0.has_seconds() ? d0.seconds() : 0.0;
    const int nminutes = static_cast<int>(std::floor(seconds))/60;
    minutes += nminutes;
    seconds -= nminutes * 60;
    const int nhours = static_cast<int>(std::floor(minutes))/60;
    hours += nhours;
    minutes -= nhours * 60;
    const int ndays = static_cast<int>(std::floor(hours))/24;
    days += ndays;
    hours -= ndays * 24;
    if (days > 0) 
      d.set_days(days, d0.has_days() && d0.days_fractional());
    if (hours > 0) 
      d.set_hours(hours, d0.has_hours() && d0.hours_fractional());
    if (minutes > 0) 
      d.set_minutes(minutes, d0.has_minutes() && d0.minutes_fractional());
    if (seconds > 0) 
      d.set_seconds(seconds, d0.has_seconds() && d0.seconds_fractional());
    return d;
  }

  Duration simplify(const Duration& duration) {
    const Duration d0 = removefractions(duration);
    Duration d{};
    // Handle months and years
    const double years = d0.has_years() ? d0.years() : 0.0;
    double months = d0.has_months() ? d0.months() : 0.0;
    months += years*12.0;
    if (months > 0) 
      d.set_months(months, d0.has_months() && d0.months_fractional());
    // Handle days, hours, minutes, seconds
    const double weeks = d0.has_weeks() ? d0.weeks() : 0.0;
    double days = d0.has_days() ? d0.days() : 0.0;
    days += weeks*7.0;
    double hours = d0.has_hours() ? d0.hours() : 0.0;
    hours += days*24.0;
    double minutes = d0.has_minutes() ? d0.minutes() : 0.0;
    minutes += hours*60.0;
    double seconds = d0.has_seconds() ? d0.seconds() : 0.0;
    seconds += minutes*60.0;
    if (!d.has_months() || seconds > 0) 
      d.set_seconds(seconds, d0.has_seconds() && d0.seconds_fractional());
    return d;
  }


  std::ostream& operator<<(std::ostream& stream, const Duration& duration) {
    bool hastime = duration.has_hours() || 
      duration.has_minutes() || duration.has_seconds();
    bool hasdate = duration.has_years() || duration.has_months() || 
      duration.has_days() || duration.has_weeks();
    stream.setf(std::ios_base::fixed);
    numprinter printnum;
    stream << 'P';
    if (duration.has_years()) printnum(stream, duration.years()) << 'Y';
    if (duration.has_months()) printnum(stream, duration.months()) << 'M';
    if (duration.has_days()) printnum(stream, duration.days()) << 'D';
    if (duration.has_weeks()) printnum(stream, duration.weeks()) << 'W';
    if (hastime) {
      stream << 'T';
      if (duration.has_hours()) printnum(stream, duration.hours()) << 'H';
      if (duration.has_minutes()) printnum(stream, duration.minutes()) << 'M';
      if (duration.has_seconds()) printnum(stream, duration.seconds()) << 'S';
    }
    // We omit values of 0 and elements that aren't set. But that could mean we
    // haven't printed anything except the 'P' which is invalid. Print a
    // duration of 0 seconds in that case.
    if (!hasdate && !hastime) stream << "T0S";
    return stream;
  }

}
