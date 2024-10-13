
pkgload::load_all()


x <- c("T12+01", "2024-01-01", "2034-W03", "FOO", NA)
res <- rcpp_type(x)
res

tz <- factor(res %% 10, levels = c(0, 1, 2), labels = c("", "Z", "±Z"))
t <- factor((res %/% 10) %% 10, levels = c(0, 1, 2, 3, 4, 5), 
  labels = c("", "TH", "THM.", "THM", "THMS.", "THMS"))
d <- factor(((res %/% 10) %/% 10) %% 10, levels = c(0, 1, 2, 3, 4, 5, 6),
  labels = c("", "Y", "YM", "YMD", "YW", "YWD", "YD"))

r <- paste0(d, t, tz)
r[is.na(res)] <- NA
r



