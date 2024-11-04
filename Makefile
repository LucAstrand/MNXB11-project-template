CXX := g++
CXXWARNINGS := -Wall -Wextra -Werror -Wno-stringop-truncation
CXXOPT := -O3
CXXSTD := -std=c++17
INCLUDES := -I include -I external/include -I /opt/apps/root/include
CXXFLAGS := $(CXXWARNINGS) $(CXXSTD) $(CXXOPT) $(INCLUDES)
LDFLAGS := -L/opt/apps/root/lib -lGui -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -Wl,-rpath,/opt/apps/root/lib -pthread -lm -ldl -rdynamic -L external/lib64 -lfmt

.PHONY: all clean

all: main

main: main.cxx src/Example.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

src/%.o: src/%.cxx
	$(CXX) $(CXXFLAGS) $^ -c -o $@

clean:
	rm -v src/*.o main