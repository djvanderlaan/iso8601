pkgload::load_all()

x <- rcpp_parse_iso_list(c("2024-W01-1", "2041-02-12T12.30Z", "ff"))
x
class(x) <- "ISO8601"

format.ISO8601 <- function(x, ...) {
  sapply(x, format)
}

format.ISO8601Date <- function(x, ...) {
  i
  sprintf("%04d-W%02d-%01d", x$year, x$week, x$weekday)
}

print.ISO8601 <- function(x, ...) {
  print(format(x))
}


