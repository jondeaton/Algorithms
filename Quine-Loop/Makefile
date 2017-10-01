PROGS = quine one two three four
CXX = g++

CXX_WARNINGS = -Wall -pedantic -Wno-vla
CXX_DEPS = -MMD -MF $(@:.o=.d)
CXX_DEFINES =
CXX_INCLUDES = -I/afs/ir/class/cs110/local/include

CXXFLAGS = $(CXX_WARNINGS) -O0 -std=c++0x $(CXX_DEPS) $(CXX_DEFINES) $(CXX_INCLUDES)

PROGS_SRC = $(patsubst %,%.cc,$(PROGS))
PROGS_OBJ = $(patsubst %.cc,%.o,$(patsubst %.S,%.o,$(PROGS_SRC)))
PROGS_DEP = $(patsubst %.o,%.d,$(PROGS_OBJ))

# all: $(PROGS)

# $(PROGS) $(EXTRA_PROGS): %:%.o
# 	$(CXX) $(CXXFLAGS) $^  -o $@

all:
	$(CXX) $(CXXFLAGS) quine.cpp -o quine
	$(CXX) $(CXXFLAGS) one.cpp -o one
	./one > two.cpp
	$(CXX) $(CXXFLAGS) two.cpp -o two
	./two > three.cpp
	$(CXX) $(CXXFLAGS) three.cpp -o three
	./three > four.cpp
	$(CXX) $(CXXFLAGS) four.cpp -o four
	rm all

clean:
	rm -f two.cpp three.cpp four.cpp $(PROGS) $(PROGS_OBJ) $(PROGS_DEP)

.PHONY: all clean
