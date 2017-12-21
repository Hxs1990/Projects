//Expression.h
#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <iostream>
#include <sstream>

class Expression{
public:
	virtual std::string prettyprint() = 0;
	virtual void set(std::string var, int num) = 0;
	virtual void unset(std::string var) = 0;
	virtual int evaluate() = 0;
	virtual ~Expression(){};
};

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
