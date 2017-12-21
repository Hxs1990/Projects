//Expression.h
#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <iostream>
#include <sstream>
#include "exception.h"
class Expression{
public:
	virtual std::string prettyprint() = 0;
	virtual void set(std::string var, int num) = 0;
	virtual void unset(std::string var) = 0;
	virtual int evaluate() = 0;
	virtual ~Expression()=0;
	virtual Expression* duplicate() = 0;
};
#endif

