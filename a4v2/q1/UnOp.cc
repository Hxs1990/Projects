#include "UnOp.h"

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
	if (op == "ABS" && check >= 0){
		return check;
	}
	else{
		return -check;
	}
}


