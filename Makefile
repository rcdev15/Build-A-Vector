CXXFLAGS = -std=c++14 -Wall -Werror

all : testmain

#=============================================================================
# How to build the binary

testmain : testmain.o vectortest.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test: testmain
	./testmain

doc:
	doxygen

clean:
	rm -rf *.o testmain docs


.PHONY: all clean test doc

#=============================================================================
# Dependencies

testmain.cpp : vectortest.h vector.h
vectortest.cpp : vectortest.h
