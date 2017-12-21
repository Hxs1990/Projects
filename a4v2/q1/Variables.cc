#include "Variables.h"

//Destructor
Variables::~Variables(){};

// Constructor: By default the variables are unset and store 0
Variables::Variables(std::string varName):
	varName{varName},isSet{false},stored{0}{}

// Prints out the name of the variable only if it's unset
// Otherwise it prints out the value the variable contains
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

// Unsets the variable thus nullifying the given value it contains
void Variables::unset(std::string var){
	if (isSet && var == varName){
		isSet = false;
	}
}

// Returns back the stored value if it's set, if it isn't it throws an error;
int Variables::evaluate(){
	if (!isSet){
		throw UnsetVariable{varName};
	}
	else{
		return stored;
	}
}

