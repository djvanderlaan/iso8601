
.PHONY: build check document install vignettes clean getlib

build: document
	cd work && R CMD build ../

check: build
	cd work && R CMD check --as-cran `ls iso8601*.tar.gz | sort | tail -n 1`

document:
	R -e "roxygen2::roxygenise()"

vignettes: build
	cd work && tar -xzf `ls iso8601*.tar.gz | sort | tail -n 1` && \
	  rm -r -f ../inst/doc && \
	  mkdir -p ../inst && \
	  cp -r iso8601/inst/doc ../inst

install: build
	R CMD INSTALL `ls work/iso8601*.tar.gz | sort | tail -n 1` 

clean: 
	rm -f src/utils.* src/iso8601* src/parse* src/determine* src/RcppExports.cpp src/*.o R/RcppExports.R

getlib: clean
	cp ../include/*.h ../src/*.cpp ./src
