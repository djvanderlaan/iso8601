
test <- list(
    sec = runif(10, 0, 60),
    min = sample(0:59, 10, replace = TRUE),
    hour = sample(0:23, 10, replace = TRUE),
    mday = sample(0:22, 10, replace = TRUE),
    mon = sample(0:22, 10, replace = TRUE),
    year = sample(0:123, 10, replace = TRUE),
    wday = rep(NA_integer_, 10),
    yday = rep(NA_integer_, 10),
    isdst = rep(-1, 10),
    zone = rep("-01", 10),
    gmtoff = rep(-1*3600, 10)
  )

isleapyear <- function(y) {
  (y %% 4 == 0) & !((y %% 100 == 0) & (y %% 400 != 0))
}

y <- 1900:2023
res<- isleapyear(y)
names(res) <- y
res

subtracthour <- function(t) {
  # subtract hour from hour
  t$hour <- t$hour - 1L
  # handle day crossing
  s <- t$hour < 0L
  t$hour[s] <- t$hour + 24L
  t$mday[s] <- t$mday - 1L;
  # handle month crossing
  s <- t$day < 1L
  t$day[s & t$mon %in% c(1, 2, 4, 6, 8, 9, 11)] <- 31L
  t$day[s & t$mon %in% c(5, 7, 10, 12)] <- 30L
  t$day[s & t$mon == 3] <- ifelse(isleapyear(t$year), 29L, 28L)
  t$mon[s] <- t$mon - 1L
  # handle year crossing
  s <- t$mon < 1L
  t$mon[s] <- 12L
  t$year[s] <- t$year - 1L
  t
}

as.POSIXlt("2023-05-01 00:00:00") |> subtracthour()



as.POSIXlt("2024-01-01 20:45:00+0100", format = "%Y-%m-%d %H:%M:%OS%z")  |> unclass()


tt <- structure(test, class = c("POSIXlt", "POSIXt"))
tt

format(tt, tz="GMT", usetz=TRUE)


moment1 <- "2021-01-05T09:00:00+01:00"
m1 <- as.POSIXlt(moment, format = "%Y-%m-%dT%H:%M:%S",
  tz = chartr("+-", "-+", sub(".*([+-])0?(.*):..$", "Etc/GMT\\1\\2", moment)))
print(m1)
m1 |> unclass()

moment2 <- "2021-01-05T09:00:00+02:00"
m2 <- as.POSIXlt(moment2, format = "%Y-%m-%dT%H:%M:%S",
  tz = chartr("+-", "-+", sub(".*([+-])0?(.*):..$", "Etc/GMT\\1\\2", moment2))) 
chartr("+-", "-+", sub(".*([+-])0?(.*):..$", "Etc/GMT\\1\\2", moment2))
print(m2)
m2 |> unclass()

moment3 <- "2021-01-05T09:00:00"
m3 <- as.POSIXlt(moment3, format = "%Y-%m-%dT%H:%M:%S",
  tz = "Etc/GMT-2") 
print(m3)
m3 |> unclass()

m1-m3

as.POSIXct(m1) - as.POSIXct(m3)

m2 - m

test <- list(
    sec = c(0L, 0L, 0L),
    min = c(0L, 0L, 0L),
    hour = c(22L, 22L, 22L),
    mday = c(1L, 1L, 1L),
    mon = c(1L, 6L, 1L),
    year = c(2024L, 2024L, 2024L)-1900L,
    wday = rep(NA_integer_, 3),
    yday = rep(NA_integer_, 3),
    isdst = rep(-1, 3),
    #zone = c("", "", ""),
    #zone = c("GMT", "CEST", "GMT"),
    zone = c("Etc/GMT+1", "Etc/GMT+1", "Etc/GMT-1"),
    gmtoff = c(-1, -1, +1) * 3600
  )
tt <- structure(test, class = c("POSIXlt", "POSIXt"), tzone = "GMT")
tt

tt - tt[3]

m1
as.POSIXct(m1, tz = "GMT")
as.POSIXct(m1)

class(tt)
as.POSIXct(tt)

moment3 <- "2021-01-05T09:00:00"
m3 <- as.POSIXlt(moment3, format = "%Y-%m-%dT%H:%M:%S",
  tz = "CET") 
m3
as.POSIXct(m3, tz = "Etc/GMT+1") |> unclass()
as.POSIXct(m3, tz = "GMT") |> unclass()



moment2 <- c("2021-01-05T09:00:00+0200","2021-01-05T09:00:00+0100")
strptime(moment2, "%Y-%m-%dT%H:%M:%OS%z", tz = "GMT")|>unclass()


