#include "UnOp.h"

// Destructor: Deletes the rest of the expression
UnOp::~UnOp(){
	delete rest;
}

// Constructor: Creates an UnOp with the rest being the rest of the expression
UnOp::UnOp(Expression *rest, std::string op):
	rest{rest},op{op}{}

// Prints the UnOp Expression
std::string UnOp::prettyprint(){
	if (op == "ABS"){
		return  '|' + rest->prettyprint() + '|';
	}
	else{
		return '-' + rest->prettyprint();
	}
}

// Sets the variables for the rest of the expression
void UnOp::set(std::string var, int value){
	rest->set(var,value);
}

// Unsets the variables for the rest of the expression
void UnOp::unset(std::string var){
	rest->unset(var);
}

// Evaluates the expression for the rest:
//  If the operator was ABS, makes the expression positive
//  If the operator was NEG, then apply the negation to the expression
int UnOp::evaluate(){
	int check = rest->evaluate();
	if (op == "ABS" && check >= 0){
		return check;
	}
	else{
		return -check;
	}
}

// Creates a deep copy of the expression
Expression* UnOp::duplicate(){
	Expression *toReturn = new UnOp(rest->duplicate(),op);
	return toReturn;
}

