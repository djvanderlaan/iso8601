
SOURCEDIR  = src
INCLUDEDIR = include
TMPDIR     = tmp
TESTSDIR   = tests

#CXX        = g++
CXX = g++ -fsanitize=address -fno-omit-frame-pointer
CXXFLAGS   = -I$(INCLUDEDIR) -I$(TESTSDIR) -Wall 
#CXXFLAGS   = -O3 -std=c++20 -I$(INCLUDEDIR) -Wall
#CXXFLAGS  = -pg -std=c++11 -I$(INCLUDEDIR) -Wall
#LIBS       = -pthread


VPATH      = $(INCLUDEDIR):$(SOURCEDIR):$(TMPDIR):$(TESTSDIR)

target     = iso8601_standardise
sources    = $(wildcard src/*.cpp)
objects    = $(notdir $(patsubst %.cpp, %.o, $(target).cpp $(sources)))

$(target): $(objects) 
	@echo "Linking..."
	@$(CXX) $(CXXFLAGS) -o $(target) $(patsubst %.o,$(TMPDIR)/%.o,$(objects)) $(LIBS)

-include $(patsubst %.d,$(TMPDIR)/%.d,$(objects:.o=.d))
	
%.o: %.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -o $(TMPDIR)/$@ -c  $<

$(TMPDIR)/%.d: %.cpp
	@echo "Making dependencies for $<..."
	@$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$;\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -f $@.$$$$

.PHONY: all clean test

all: $(target) 

clean:
	@echo "Cleaning up..."
	@/bin/rm -f $(TMPDIR)/*.o $(TMPDIR)/*.d $(target) $(target_tests)


target_tests     = iso8601_test
sources_tests    = $(wildcard tests/*.cpp)
objects_tests    = $(notdir $(patsubst %.cpp, %.o, $(sources) $(sources_tests)))

#$(info objects_tests = $(objects_tests))
#$(info vpath = $(VPATH))

$(target_tests): $(objects_tests)
	@echo "Linking tests..."
	@$(CXX) $(CXXFLAGS) -o $(target_tests) $(patsubst %.o,$(TMPDIR)/%.o,$(objects_tests)) $(LIBS)

test: iso8601_test
	@echo "Running tests..."
	@./iso8601_test
