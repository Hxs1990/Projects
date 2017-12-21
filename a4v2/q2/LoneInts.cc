#include "LoneInts.h"

// Destructor
LoneInts::~LoneInts(){}

// Constructor
LoneInts::LoneInts(const int &value): num{value}{}

// Returns the string version of int
std::string LoneInts::prettyprint(){
	return std::to_string(num);
}

// No implementation 
void LoneInts::set(std::string var, int value){}

// No implementation
void LoneInts::unset(std::string var){}

// Returns the int value stored back
int LoneInts::evaluate(){
	return num;
}

// Returns a copy of the expression object
Expression* LoneInts::duplicate(){
	Expression *toReturn = new LoneInts(num);
	return toReturn;
}

