//Expression.cc
#include "expression.h"

// BINARY OPERATORS
BinOp::~BinOp(){
	delete left;
	delete right;
}

BinOp::BinOp(Expression *left,Expression *right, std::string op):
	left{left}, right{right}, op{op}{}

std::string BinOp::prettyprint(){
	return '('+left->prettyprint()+" "+ op+ " "+right->prettyprint()+')';
}

void BinOp::set(std::string var, int value){
	left->set(var,value);
	right->set(var,value);
}

void BinOp::unset(std::string var){
	left->unset(var);
	right->unset(var);
}

int BinOp::evaluate(){
	if (op == "+") return (left->evaluate() + right->evaluate());
	if (op == "-") return (left->evaluate() - right->evaluate());
	if (op == "*") return (left->evaluate() * right->evaluate());
	else {
		return (left->evaluate() / right->evaluate());
	}	
}

// UNIARY OPERATORS
UnOp::~UnOp(){
	delete rest;
}

UnOp::UnOp(Expression *rest, std::string op):
	rest{rest},op{op}{}


std::string UnOp::prettyprint(){
	if (op == "ABS"){
		return  '|' + rest->prettyprint() + '|';
	}
	else{
		return '-' + rest->prettyprint();
	}
}

void UnOp::set(std::string var, int value){
	rest->set(var,value);
}

void UnOp::unset(std::string var){
	rest->unset(var);
}

int UnOp::evaluate(){
	int check = rest->evaluate();
	if (check < 0){
		return -(check);
	}
	return check;
}


//LONE INTEGERS

LoneInts::~LoneInts(){}
LoneInts::LoneInts(const int &value): num{value}{}

std::string LoneInts::prettyprint(){
	return std::to_string(num);
}

void LoneInts::set(std::string var, int value){}

void LoneInts::unset(std::string var){}

int LoneInts::evaluate(){
	return num;
}


// VARIABLES
Variables::~Variables(){};
Variables::Variables(std::string varName):
	varName{varName},isSet{false},stored{0}{}

std::string Variables::prettyprint(){
	if (isSet) return std::to_string(stored);
	else{
		return varName;
	}
}

void Variables::set(std::string var, int value){
	if (!isSet && var == varName){
		isSet = true;
		varName = var;
		stored = value;
	}
}

void Variables::unset(std::string var){
	if (isSet && var == varName){
		isSet = false;
	}
}
int Variables::evaluate(){
	if (!isSet){
		throw "unset_var: " + varName;
	}
	else{
		return stored;
	}
}









