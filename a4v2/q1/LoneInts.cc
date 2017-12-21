#include "LoneInts.h"

//Destructor
LoneInts::~LoneInts(){}

//Constructor
LoneInts::LoneInts(const int &value): num{value}{}

//Returns the string of the number stored
std::string LoneInts::prettyprint(){
	return std::to_string(num);
}

//No functionality
void LoneInts::set(std::string var, int value){}

//No functionality
void LoneInts::unset(std::string var){}

//Returns the value stored as the int intepretation
int LoneInts::evaluate(){
	return num;
}

