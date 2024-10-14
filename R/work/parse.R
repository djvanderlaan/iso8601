pkgload::load_all()


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
