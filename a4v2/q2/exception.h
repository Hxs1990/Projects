//exception.h
#ifndef EXPRESSIONEXCEPTION_H
#define EXPRESSIONEXCEPTION_H
#include <string>

class UnsetVariable{
	std::string s;
public:
	UnsetVariable(std::string s);
	std::string what();
};

#endif

