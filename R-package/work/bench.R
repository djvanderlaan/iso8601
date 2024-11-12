
x <- as.Date(seq(0:10000))
x <- sample(x, 1E6, replace = TRUE)
x[rbinom(length(x), 1, 0.02) == 1] <- NA
x <- as.character(x)

#library(iso8601)
pkgload::load_all()
library(lubridate)
library(anytime)
library(parsedate)


t0 <- system.time({
d0 <- as.Date(x)
})
t0

t1 <- system.time({
d1 <- iso8601todate(x)
})
t1
all(is.na(d1) | d1 == d0)

t2 <- system.time({
d2 <- anydate(x)
})
t2
all(is.na(d2) | d2 == d0)


t3 <- system.time({
d3 <- ymd(x)
})
t3
all(is.na(d3) | d3 == d0)

t4 <- system.time({
  d4 <- parse_iso_8601(x)
})
t4
all(is.na(d4) | d4 == d0)


n <- 1E6
x <- as.POSIXct(round(runif(n, 0, 1E9)))
x[rbinom(length(x), 1, 0.02) == 1] <- NA
x <- strftime(x, "%Y-%m-%d %H:%M:%S")

t0 <- system.time({
d0 <- as.POSIXct(x)
})
t0


t1 <- system.time({
d1 <- iso8601todatetime(x)
})
t1
all(is.na(d0) | d1 == d0)
s <- which(!(is.na(d0) | d1 == d0))

x[s]
d1[s]

t2 <- system.time({
d2 <- anytime(x)
})
t2
all(is.na(d2) | d2 == d0)


t3 <- system.time({
d3 <- ymd_hms(x)
})
t3
all(is.na(d3) | d3 == d0)


hmm <- c("1984-07-27 04:15:50.272495", "2000-04-24 02:16:07.993638",
"1983-07-13 22:02:13.591419", "2001-04-15 08:03:20.730315", "1997-10-07 21:06:09.480383",
"1983-07-03 18:23:02.092848")

hmm <- "1985-12-27 05:43:25"
a <- as.POSIXct(hmm[1]) 
b0 <- as.POSIXlt(hmm[1])
b <- as.POSIXlt(hmm[1]) |> as.POSIXct()
a == b

iso8601todataframe(hmm[1])
c <- iso8601todatetime(hmm[1])

t <- list(sec = 6L, min = 14L, hour = 3L, mday = 25L, mon = 10L - 1L, 
  year = 1999L-1900L, wday = NA_integer_, yday = NA_integer_, isdst = -1L, zone = "", gmtoff = NA_integer_)
t <- structure(t, class = c("POSIXlt", "POSIXt"), timezone = c("", "CET", "CEST"))

t

x

t |> as.POSIXct()  
t |> as.POSIXct()  |> unclass()
unclass(as.POSIXct("1999-10-25 03:14:06"))

t 

unclass(d0)

unclass(b0)

