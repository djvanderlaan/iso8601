pkgload::load_all()


res <- parsedatetime(c("2024-01-01T12:30", "2024-01-01T12:30Z"))
res
unclass(res)
class(res)

x <- res
result <- character(length(res))
(zones <- unique(x$zone))
for (zone in zones) {
  sel <-x$zone == zone
  result[sel] <- as.POSIXct(x[sel], tz = zone)
}
result



(sel_local <- r$zone == "")
local <- list()
for (n in names(r))
  local[[n]] <- r[[n]][sel_local]
local
local <- structure(local, class = c("POSIXlt", "POSIXt"), tzone = c(""))
local

local <- as.POSIXct(local)
r <- as.POSIXct(res)
r[sel_local] <- local
attr(r, "tzone") <- attr(local, "tzone")
r

d <- data.frame(res = res, r=r)
d
d$res

res

unclass(d$res)

res
res$sec[] <- NA
res$min[] <- NA
res



x <- c("2024-01-01T12:30", "2024-01-01T12:30Z")
res <- rcpp_parse_datetime(x)
n <- length(x)
res$year <- res$year - 1900L
res$wday <- rep(NA_integer_, n)
res$yday <- rep(NA_integer_, n)
res$isdst <- rep(0L, n)
res$gmtoff <- ifelse(res$zone == "Z", 0L, NA_integer_) 
res <- res[c("sec", "min", "hour", "mday", "mon", "year", "wday", 
  "yday", "isdst", "zone", "gmtoff")]
local <- all(res$zone == "")
gmt <- all(res$zone != "")
tzone <- if (local) "" else "GMT"
res$zone[res$zone != ""] <- "GMT"
if (!local && !gmt)
  warning("Mix of local time zone and GMT. Assuming GMT is local time.")
structure(res, tzone = tzone, class = c("POSIXlt", "POSIXT"))








res <- parsedatetime(c("2024-01-01T12:30Z", "2024-01-01T12:30Z"))
res
unclass(res)

res <- parsedatetime(c("2024-01-01T12:30", "2024-01-01T12:30Z"))
res

t1 <- parsedatetime("2024-01-01T12:30")
t1 <- as.POSIXct(t1)
t1
unclass(t1)

t2 <- parsedatetime("2024-01-01T12:30Z")
t2 <- as.POSIXct(t2) 
t2
unclass(t2)

t1
t2
attr(t2, "tzone") <- ""
t2

t1 <- as.POSIXct("2024-01-01 12:30")
t2 <- as.POSIXct("2024-01-01 12:30", tz = "GMT")
t3 <- t2
attr(t3, "tzone") <- ""
t1
t2
t3

t4 <- t3 |> as.POSIXlt() 
unclass(t4)
t4$zone <- "GMT"
t4
as.POSIXct(t4) |> unclass()
attr(t4, "tzone") <- "GMT"
t4
as.POSIXct(t4) |> unclass()

t1 <- as.POSIXlt("2024-01-01 12:30")
t2 <- as.POSIXlt("2024-01-01 12:30", tz = "GMT")
t3 <- t2
attr(t3, "tzone") <- ""
t1
t2
t3

as.POSIXlt("2024-01-01 12:30", tz = "GMT") |> unclass()

It is not completely clear to me how time zones work with POSIXlt objects. For
POSIXct, I can understand what happend: time is always stored as GMT, the
`tzone` attribute only affects how the times are displayed. All computations
etc. are done in GMT.

POSIXlt objects have both a `tzone` attribute and a `zone` field. It seems that
the `zone` field is completely ignored. It only seems to uses when displaying
the times, but does not seem to play a role when doing arithmetic and
conversions of the times.

For example below, we have the same times in two different time zones. The
following seems to do what I expect: when we subtract the two times we get the
difference in time between the two time zones:

t1 <- as.POSIXlt(c("2024-01-01 12:30", "2024-01-01 12:30"), tz = "GMT")
t1$zone
# [1] "GMT" "GMT"
t2 <- as.POSIXlt(c("2024-01-01 12:30", "2024-01-01 12:30"))
t2$zone
# [1] "CET" "CET"
t1 - t2
# Time differences in hours
# [1] 1 1


When I change the `tzone` attribute of t1 to that of t2:

attr(t1, "tzone") <- attr(t2, "tzone")
t1
#[1] "2024-01-01 12:30:00 GMT" "2024-01-01 12:30:00 GMT"

The times are still displayed as being in GMT, however when I take the
difference:

t1 - t2
#Time differences in secs
#[1] 0 0

We get a difference of 0. So it seems that the difference is only based on the
`tzone` attribute. The value of `zone` is completely ignored.

I am aware of the following remark in ?POSIXlt on arithmetic operations
| Be aware that ‘"POSIXlt"’ objects will be interpreted as being in the current
| time zone for these operations unless a time zone has been specified.

but this does not explain this, I think. 

One of the reasons, I ask, is that I have (potentially) times in different time
zones. Using POXIXlt objects seemes like they could store/support this. But
working with this seems unpractical as the `zone` field does not seem to do
anything:

t1$zone <- c("CET", "GMT")
t1 - t2
#Time differences in secs
#[1] 0 0

Also the `gmtoff` field does not seem to do anything. For what/where is this
field used?

t1$gmtoff <- c(3600, 0)
t1
#[1] "2024-01-01 12:30:00 CET" "2024-01-01 12:30:00 GMT"
t1 - t2
#Time differences in secs
#[1] 0 0
as.POSIXct(t1)
#[1] "2024-01-01 12:30:00 CET" "2024-01-01 12:30:00 CET"


The reason I am asking the above, it that I have some times in potentially
different time zones. The data I get is something like:

times <- list(
  year = c(2024L, 2024L),
  month = c(1L, 1L),
  day = c(1L, 1L),
  hour = c(12L, 12L),
  minutes = c(30L, 30L),
  seconds = c(0, 0),
  timezone = c("", "GMT")
)

I am looking for ways to convert this into a practical data format for working
with in R. The possible time zones only local time or UTC/GMT. I would be fine
with either converting local time to GMT.



