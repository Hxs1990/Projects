CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = a3q4
OBJECTS = a3q4.o node.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
