#ifndef BINOP_H
#define BINOP_H
#include "expression.h"

class BinOp: public Expression{
	Expression *left = nullptr;
	Expression *right = nullptr;
	std::string op;
public:
	~BinOp();
	BinOp(Expression *left, Expression *right, std::string op); 
	std::string prettyprint() override;
	void set(std::string var, int value) override;
	void unset(std::string var) override;
	int evaluate() override;
	Expression* duplicate() override;
};
#endif

