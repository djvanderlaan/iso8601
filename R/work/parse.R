pkgload::load_all()

format.ISO8601 <- function(x, ...) {
  sapply(x, format)
}
format.ISO8601Date <- function(x, ...) {
  paste0(
    sprintf("%04d", x$year),
    sprintf("-%02d", x$month),
    sprintf("-%02d", x$day),
    sprintf("-W%02d", x$week),
    sprintf("-%01d", x$weekday),
    sprintf("-%03d", x$yearday)
  )
}
format.ISO8601TimeZone <- function(x, ...) {
  if (hasName(x, "tz_offset_hours")) {
    if (x$tz_offset_hours == 0 && x$tz_offset_minutes == 0) {
      "Z"
    } else {
      sign <- if (x$tz_offset_hours > 0) "+" else "-"
      print(sign)
      sprintf("%s%02d:%02d", sign, abs(x$tz_offset_hours), x$tz_offset_minutes)
    }
  } else {
    ""
  }
}
format.ISO8601Time <- function(x, ...) {
  paste0(
    sprintf("T%02d", x$hour),
    sprintf(":%02d", x$minutes),
    sprintf(":%02d", x$seconds),
    format.ISO8601TimeZone(x)
  )
}
format.ISO8601DateTime <- function(x, ...) {
  paste0(format.ISO8601Date(x), format.ISO8601Time(x))
}


print.ISO8601 <- function(x, ...) {
  print(format(x))
}

as.data.frame.ISO8601 <- function(x, row.names = NULL, optional = FALSE, ..., nm = deparse1(substitute(x))) {
  force(nm)
  nrows <- length(x)
  if (is.null(row.names) && nrows == 0) {
    row.names = character(0)
  } else if (is.null(row.names) && !is.null(names(x))) {
    row.names = names(x)
  } else if (is.null(row.names)) {
    row.names = seq_len(nrows)
  }
  stopifnot(is.character(row.names) || is.integer(row.names))
  stopifnot(length(row.names) == nrows)
  if (!is.null(names(x))) names(x) <- NULL
  res <- list(x)
  if (!optional) names(res) <- nm
  structure(res, row.names = row.names, class = "data.frame")
}

`[.ISO8601` <- function(x, ..., drop = TRUE) {
  structure(NextMethod("["), class=  oldClass(x))
}

x <- rcpp_parse_iso_list(c("2024-W01-1", "2041-02-12T12+00:00", "ff", "T22"))
class(x) <- "ISO8601"
x

x[[2]]


sapply(x, class)

x

as.data.frame.ISO8601(x)


data.frame(x = x)

x <- c("2024-W01-1", "2041-02-12T12+00:00", "ff", "T22")
x <- sample(x, 1E4, replace = TRUE)
system.time({
res <- rcpp_parse_iso_list(x)
})
class(res) <- "ISO8601"
res

data.frame(x = res)  |> head()

head(res)
