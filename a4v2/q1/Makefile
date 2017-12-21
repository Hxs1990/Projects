CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla 
EXEC = a4q1
OBJECTS = main.o BinOp.o exception.o expression.o LoneInts.o UnOp.o Variables.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

