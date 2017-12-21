//exception.cc
#include "exception.h"

UnsetVariable::UnsetVariable(std::string s):s{s}{}


std::string UnsetVariable::what(){
	return s;
}

