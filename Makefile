
ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --glibs)

# Define targets and rules
main: main.o
	g++ main.o -o main $(ROOTLIBS)

main.o: main.cxx
	g++ -c main.cxx $(ROOTCFLAGS)

# Clean up compiled files
clean:
	rm -f main.o main

CXX := g++
CXXWARNINGS := -Wall -Wextra -Werror -Wno-stringop-truncation
CXXOPT := -O3
CXXSTD := -std=c++17
INCLUDES := -I include -I external/include -I /opt/apps/root/include
CXXFLAGS := $(CXXWARNINGS) $(CXXSTD) $(CXXOPT) $(INCLUDES)
LDFLAGS := -L/opt/apps/root/lib -lGui -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -Wl,-rpath,/opt/apps/root/lib -pthread -lm -ldl -rdynamic -L external/lib64 -lfmt

.PHONY: all clean

all: main



