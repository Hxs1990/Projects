#ifndef UNOP_H
#define UNOP_H
#include "expression.h"
class UnOp: public Expression{
	Expression *rest = nullptr;
	std::string op;
public:
	~UnOp();
	UnOp(Expression *rest, std::string op);
	std::string prettyprint() override;
	void set(std::string var, int value) override;
	void unset(std::string var) override;
	int evaluate() override;
	Expression* duplicate() override;
};

#endif

