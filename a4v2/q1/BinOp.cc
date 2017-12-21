#include "BinOp.h"

//Deletes the left and right side of the expression
BinOp::~BinOp(){
	delete left;
	delete right;
}

// Constructor
BinOp::BinOp(Expression *left,Expression *right, std::string op):
	left{left}, right{right}, op{op}{}

// Returns a string of the left and the right with the
//  operator in the middle surrounded with brackets
std::string BinOp::prettyprint(){
	return '('+left->prettyprint()+" "+ op+ " "+right->prettyprint()+')';
}
// Sets the var for the left and the right
void BinOp::set(std::string var, int value){
	left->set(var,value);
	right->set(var,value);
}
// Unsets the var for the left and the right
void BinOp::unset(std::string var){
	left->unset(var);
	right->unset(var);
}
// Evalutes the value between the left and right expression
int BinOp::evaluate(){
	if (op == "+") return (left->evaluate() + right->evaluate());
	if (op == "-") return (left->evaluate() - right->evaluate());
	if (op == "*") return (left->evaluate() * right->evaluate());
	else {
		return (left->evaluate() / right->evaluate());
	}	
}



