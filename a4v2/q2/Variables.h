#ifndef VARIABLES_H
#define VARIABLES_H

#include "expression.h"
class Variables:public Expression{
	std::string varName;
	bool isSet;
	int stored;
public:
	~Variables();
	Variables(std::string varName);
	std::string prettyprint() override;
	void set(std::string var, int value) override;
	void unset(std::string var) override;
	int evaluate() override;
	Expression* duplicate() override; 
};
#endif

