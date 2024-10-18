

# `iso8601` R-package 


```{.R}
library(iso8601)
iso8601todate("2019-08-17")
iso8601todatetime("2019-08-17T16:15:14Z")
iso8601totime("T16:15:14")
```

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
```

```{.R}
iso8601todatetime("2019-08-17T16:15:14Z")
iso8601todatetime("2019-08-17T16:15:14,00Z")
iso8601todatetime("2019-08-17T16:15:14.00Z")
iso8601todatetime("2019-08-17T161514Z")
iso8601todatetime("2019-08-17T161514.00Z")
iso8601todatetime("2019-08-17T161514,00Z")

# Fractional times
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

# When the date and time are in extended format 
# the T can be omitted
iso8601todatetime("2019-08-17 16:15:14Z")
iso8601todatetime("2019-08-17 16:15:14,00Z")
iso8601todatetime("2019-08-17 16:15:14.00Z")
iso8601todatetime("2019-08-17 16:15:14,00Z")
iso8601todatetime("2019-08-17 16:15:14.00Z")
iso8601todatetime("2019-08-17 16:15.24Z")
iso8601todatetime("2019-08-17 16:15,24Z")
```

```{.R}
iso8601todatetime("2019-08-17T16:15:14Z")
iso8601todatetime("2019-08-17T16:15:14+01:00")
iso8601todatetime("2019-08-17T16:15:14+01")
iso8601todatetime("2019-08-17T16:15:14")
```

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

```{.R}
iso8601totime("T16:15:14Z")
iso8601totime("T16:15:14,00Z")
iso8601totime("T16:15:14.00Z")
iso8601totime("T161514Z")
iso8601totime("T161514.00Z")
iso8601totime("T161514,00Z")
iso8601totime("T16:15:14,00Z")
iso8601totime("T16:15:14.00Z")
iso8601totime("T161514.00Z")
iso8601totime("T161514,00Z")
iso8601totime("T16:15.24Z")
iso8601totime("T16:15,24Z")
iso8601totime("T1615.24Z")
iso8601totime("T1615,24Z")
iso8601totime("T16.2539Z")
iso8601totime("T16,2539Z")

# When time is in extended format T can be omitted
iso8601totime("16:15:14Z")
iso8601totime("16:15:14,00Z")
iso8601totime("16:15:14.00Z")
iso8601totime("16:15:14,00Z")
iso8601totime("16:15:14.00Z")
iso8601totime("16:15.24Z")
iso8601totime("16:15,24Z")
```

```{.R}
t <- iso8601totime("T16:15:14Z")
print(t)
class(t)
class(t) <- class(t)[-1]
print(t)
```


