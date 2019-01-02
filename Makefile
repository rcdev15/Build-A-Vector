CXXFLAGS = -std=c++17 -Wno-noexcept-type -Wall -Werror


all : testmain

testmain : testmain.o vectortest.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

test: testmain
	./testmain

doc:
	doxygen

clean:
	rm -rf *.o testmain docs


.PHONY: all clean test doc

# Dependencies
testmain.cpp : vectortest.h vector.h
vectortest.cpp : vectortest.h
