

# `iso8601` R-package 

The package has special functions for transforming ISO8601 strings into dates,
date-times and times. These functions transform the strings into the
corresponding R objects: ‘Date’, ‘POSIXct’ and ‘Time’ (which is a subclass of
‘POSIXct’, see below):
```{.R}
library(iso8601)
iso8601todate("2019-08-17")
iso8601todatetime("2019-08-17T16:15:14Z")
iso8601totime("T16:15:14")
```

### Dates

For converting to ‘Date’ the package should accept all valid formats described
by ISO8601 as shown below:
```{.R}
iso8601todate("2019-08-17")
iso8601todate("2019-08")
iso8601todate("2019")
iso8601todate("20190817")
iso8601todate("2019-W33-6")
iso8601todate("2019-W33")
iso8601todate("2019W336")
iso8601todate("2019W33")
iso8601todate("2019-229")
iso8601todate("2019229")
iso8601todate("−0009-123")
iso8601todate("-0009")
```
As can be seen from the examples above, for incomplete dates, the missing parts
are substituted by 1 as the ‘Date’ object cannot handle incomplete dates. It is
also possible to mix different formats in one character vector.

### Date-times

Date-time strings consist of a date and a time separated by the character ‘T’.
For the date part all complete date strings mentioned above are allowed. The
time part can be specified both in expanded format (with colon) and compact
format and as complete or incomplete times. In the latter case the missing parts
are subsituted by 0:

```{.R}
iso8601todatetime("2019-08-17T16:15:14Z")
iso8601todatetime("2019-08-17T161514Z")
iso8601todatetime("2019-08-17T16:15Z")
iso8601todatetime("2019-08-17T1615")
iso8601todatetime("2019-08-17T16Z")
```

Fractional times are also allowed:

```{.R}
iso8601todatetime("2019-08-17T16:15:14,00Z")
iso8601todatetime("2019-08-17T16:15:14.00Z")
iso8601todatetime("2019-08-17T161514.00Z")
iso8601todatetime("2019-08-17T161514,00Z")
iso8601todatetime("2019-08-17T16:15.24Z")
iso8601todatetime("2019-08-17T16:15,24Z")
iso8601todatetime("2019-08-17T1615.24Z")
iso8601todatetime("2019-08-17T1615,24Z")
iso8601todatetime("2019-08-17T16.2539Z")
iso8601todatetime("2019-08-17T16,2539Z")
```
When the date and time are in extended format the ‘T’ can be omitted

```{.R}
iso8601todatetime("2019-08-17 16:15:14Z")
iso8601todatetime("2019-08-17 16:15:14,00Z")
iso8601todatetime("2019-08-17 16:15:14.00Z")
iso8601todatetime("2019-08-17 16:15:14,00Z")
iso8601todatetime("2019-08-17 16:15:14.00Z")
iso8601todatetime("2019-08-17 16:15.24Z")
iso8601todatetime("2019-08-17 16:15,24Z")
```

Time-zones can be indicated by ‘Z’ (as in the examples above) which indicates
UTC or Zulu time; or by an offset in hours or hours and minutes. When there is
no time-zone indicator it is assumed that the times are in local time. Which
time zone that is should be communicated otherwise; the package assumes it is
the local time of the system on which R is running. A positive offset indicates
time zones east of the prime meridian whose times are ahead of UTC and negative
offsets indicate time zones west of the prime meridian.

```{.R}
iso8601todatetime("2019-08-17T16:15:14Z")
iso8601todatetime("2019-08-17T16:15:14+01:00")
iso8601todatetime("2019-08-17T16:15:14±00:00")
iso8601todatetime("2019-08-17T16:15:14-01")
iso8601todatetime("2019-08-17T16:15:14−00:00")
iso8601todatetime("2019-08-17T16:15:14")
```

As shown above, when all date-times have either an offset or are in UTC, the
times are converted and shown in UTC (for which R uses the string ‘GMT’).
Otherwise, the date-times are shown in the local time zone.

`iso8601todatetime` returns a ‘POSIXct’ object that has an additional ‘timezone’
attribute that contains the original time zones:

```{.R}
t <- iso8601todatetime(c(
    "2019-08-17T16:15:14+01:00",
    "2019-08-17T16:15:14+00",
    "2019-08-17T16:15:14Z",
    "2019-08-17T16:15:14",
    "2019-08-17T16:15:14-05:30"
  )) 
print(t)
attr(t, "timezone")
```

### Times

The `iso8601totime` converts times (without date). It accepts the following
formats:

```{.R}
iso8601totime("T16:15:14")
iso8601totime("T16:15:14,00")
iso8601totime("T16:15:14.00")
iso8601totime("T161514")
iso8601totime("T161514.00")
iso8601totime("T161514,00")
iso8601totime("T16:15:14,00")
iso8601totime("T16:15:14.00")
iso8601totime("T161514.00")
iso8601totime("T161514,00")
iso8601totime("T16:15.24")
iso8601totime("T16:15,24")
iso8601totime("T1615.24")
iso8601totime("T1615,24")
iso8601totime("T16.2539")
iso8601totime("T16,2539")
```

When time is in extended format the ‘T’ can be omitted

```{.R}
iso8601totime("16:15:14")
iso8601totime("16:15:14,00")
iso8601totime("16:15:14.00")
iso8601totime("16:15:14,00")
iso8601totime("16:15:14.00")
iso8601totime("16:15.24")
iso8601totime("16:15,24")
```

Time zones are ignored as these are meaningless without date.

The object returned is of class `c("Time", "POSIXct", "POSIXt")`. It is
therefore a subclass of ‘POSIXct’. As this object encodes date-times, the times
are encoded as times on 1970-01-01. The ‘Time’ class handles proper display of
the object. Otherwise, it can be handled are a regular ‘POSIXct’ object.

```{.R}
t <- iso8601totime("T16:15:14Z")
print(t)
class(t)
class(t) <- class(t)[-1]
print(t)
```

### Generic conversion

The function `iso8601todataframe` will parse ISO8601 strings and split these
into the separate parts. Only the parts present in any of the strings are
returned.
```{.R}
iso8601todataframe(c(
  "2019-08-17",
  "2019-W33-6",
  "2019-08-17T16:15:14+00",
  "2019229T161514",
  "T16:15"
))
```
The ‘type’ column contains the type of ISO8601 string. For parts not present in
the string \code{NA} is returned.

It is also possible to transform the dates to one format: either year-month-day
or year-day:

```{.R}
iso8601todataframe(c(
  "2019-08-17",
  "2019-W33-6",
  "2019-08-17T16:15:14+01",
  "2019229T161514",
  "T16:15"
), transformdate = "toyearmonthday")

iso8601todataframe(c(
  "2019-08-17",
  "2019-W33-6",
  "2019-08-17T16:15:14+01",
  "2019229T161514",
  "T16:15"
), transformdate = "toyearday")
```

### Helper functions

`iso8601type` returns a character vector whose elements indicate the type of ISO8601 string:
```{.R}
iso8601type(c(
  "2019-08-17",
  "2019-W33-6",
  "2019-08-17T16:15:14+01",
  "2019229T161514",
  "T16:15"
  ))
```

`iso8601standardise` transforms the dates into one standard extended format:
```{.R}
iso8601standardise(c(
  "2019-08-17",
  "2019-W33-6",
  "2019-08-17 16:15:14+01",
  "2019229T161514",
  "T16:15"
  ))
```

The `fillmissing` arguments fills in missing parts (1 for dates and 0 for
times), `toymd` transforms all dates to year-month-day and `tozulu` applies any
time zone offsets and transforms the times to UTC (times local time zones are
not affected):
```
iso8601standardise(c(
  "2019-08-17",
  "2019-W33-6",
  "2019-08-17 16:15:14+01",
  "2019229T161514",
  "T16:15"
  ), fillmissing = TRUE, toymd = TRUE, tozulu = TRUE)
```


