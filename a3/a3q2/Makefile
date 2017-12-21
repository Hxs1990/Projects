CXX = g++
CXXFLAGS = -std=c++14 -Wall -g

a3q2: a3q2.o tstring.o tnode.o utility.o
	${CXX} ${CXXFLAGS} a3q2.o tstring.o tnode.o utility.o  -o a3q2

tnode.o: tnode.cc tnode.h
	${CXX} ${CXXFLAGS} -c tnode.cc

tstring.o: tstring.cc tstring.h
	${CXX} ${CXXFLAGS} -c tstring.cc

a3q2.o: a3q2.cc tstring.h
	${CXX} ${CXXFLAGS} -c a3q2.cc

.PHONY: clean

clean:
	rm tstring.o a3q2.o tnode.o  a3q2

