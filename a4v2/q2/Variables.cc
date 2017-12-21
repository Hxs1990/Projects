#include "Variables.h"
#include "exception.h"

// Destructor
Variables::~Variables(){};

// Constructor
Variables::Variables(std::string varName):
	varName{varName},isSet{false},stored{0}{}

// Returns the var name if its unset,
// otherwise it prints out the value stored
std::string Variables::prettyprint(){
	if (isSet) return std::to_string(stored);
	else{
		return varName;
	}
}

// Sets the variable to the given value
void Variables::set(std::string var, int value){
	if (!isSet && var == varName){
		isSet = true;
		varName = var;
		stored = value;
	}
	else if (isSet && var == varName){
		varName = var;
		stored = value;
	}	
}

// Unsets the variable, nulifying the value set.
void Variables::unset(std::string var){
	if (isSet && var == varName){
		isSet = false;
	}
}
// Returns the value set to the variable, otherwise
// throws an exception
int Variables::evaluate(){
	if (!isSet){
		throw UnsetVariable{varName};
	}
	else{
		return stored;
	}
}

// Returns a copy of the Variable
Expression* Variables::duplicate(){
	Expression *toReturn = new Variables(varName);
	if (isSet){
		toReturn->unset(varName);
		toReturn->set(varName,stored);
	}
	return toReturn;
}

