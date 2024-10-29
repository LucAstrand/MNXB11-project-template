# Set ROOT paths using root-config
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