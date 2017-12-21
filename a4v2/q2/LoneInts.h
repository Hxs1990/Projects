#ifndef LONEINTS_H
#define LONEINTS_H
#include "expression.h"
class LoneInts:public Expression{
	int num;
public:
	~LoneInts();
	LoneInts(const int &value);
	std::string prettyprint() override;
	void set(std::string var, int value) override;
	void unset(std::string var) override;
	int evaluate() override;
	Expression* duplicate() override;  
};

#endif

