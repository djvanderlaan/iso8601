
datetype <- function(x) {
  levels <- c("YEAR", "YEARMONTHDAY", "YEARWEEKDAY", "YEARDAY")
  if (hasName(x, "month")) {
    return(factor("YEARMONTHDAY", levels = levels))
  }
  if (hasName(x, "week")) {
    return(factor("YEARWEEKDAY", levels = levels))
  }
  if (hasName(x, "yearday")) {
    return(factor("YEARDAY", levels = levels))
  }
  return(factor("YEAR", levels = levels))
}

format.ISO8601Date <- function(x, ...) {
  type <- datetype(x)
  if (type == "YEAR") {
    sprintf("%04d", x$year)
  } else if (type == "YEARMONTHDAY") {
    sprintf("%04d-%02d-%02d", x$year, x$month, x$day)
  } else if (type == "YEARWEEKDAY") {
    sprintf("%04d-W%02d-%01d", x$year, x$week, x$weekday)
  } else if (type == "YEARDAY") {
    sprintf("%04d-%03d", x$year, x$yearday)
  }
}
print.ISO8601Date <- function(x, ...) {
  print(format(x))
}

format.ISO8601Time <- function(x, ...) {
  sprintf("T%02.0f:%02.0f:%02.0f", x$hour, x$minutes, x$seconds) 
}
print.ISO8601Time <- function(x, ...) {
  print(format(x))
}

format.ISO8601 <- function(x, ...) {
  sapply(x, format, ...)
}
print.ISO8601 <- function(x, ...) {
  print(format(x))
}
as.data.frame.ISO8601 <- function(x, row.names = NULL, optional = FALSE, ...) {
  value <- as.data.frame.vector(x, row.names, optional, ...)
  if (!optional) names(value) <- deparse1(substitute(x))
  value
}



d  <- list(
    year = 2024,
    month = 9,
    day = 27
  )
d <- structure(d, class="ISO8601Date")
d

t  <- list(
    hour = 17,
    minutes = 15,
    seconds = 3.2
  )
t <- structure(t, class="ISO8601Time")
t

v <- list(t, d, t)
v <- structure(v, class="ISO8601")
v

as.data.frame(v)

data.frame(a = 1:3, b = v)

