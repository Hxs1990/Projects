#include "BinOp.h"

// Destructor: Deletes the left and then the right expressions
BinOp::~BinOp(){
	delete left;
	delete right;
}

// Constructor: Creates the left and right pointing to expressions
BinOp::BinOp(Expression *left,Expression *right, std::string op):
	left{left}, right{right}, op{op}{}

// Returns a string with the left and right with the
//  operator in the middle all surrounded by brackets
std::string BinOp::prettyprint(){
	return '('+left->prettyprint()+" "+ op+ " "+right->prettyprint()+')';
}

// Sets the variables to the left and right of the expressions
void BinOp::set(std::string var, int value){
	left->set(var,value);
	right->set(var,value);
}

// Unsets the variables to the left and right of the expressions
void BinOp::unset(std::string var){
	left->unset(var);
	right->unset(var);
}

// Evaluates the expression on the left and on the right of the operator
// then evaluates the whole expression
int BinOp::evaluate(){
	if (op == "+") return (left->evaluate() + right->evaluate());
	if (op == "-") return (left->evaluate() - right->evaluate());
	if (op == "*") return (left->evaluate() * right->evaluate());
	else {
		return (left->evaluate() / right->evaluate());
	}	
}

// Returns a copy of the BinOp expression
Expression* BinOp::duplicate(){
	Expression *toReturn = new BinOp(left->duplicate(),right->duplicate(),op);
	return toReturn;
}

