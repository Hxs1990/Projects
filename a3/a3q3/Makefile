CXX = g++
CXXFLAGS = -std=c++14 -Wall -g

a3q3: a3q3.o polynomial.o rational.o
	${CXX} ${CXXFLAGS} a3q3.o polynomial.o rational.o -o a3q3

polynomial.o: polynomial.cc polynomial.h
	${CXX} ${CXXFLAGS} -c polynomial.cc

a3q3.o: a3q3.cc rational.h polynomial.h
	${CXX} ${CXXFLAGS} -c a3q3.cc

.PHONY: clean

clean:
	rm a3q3.o polynomial.o a3q3
