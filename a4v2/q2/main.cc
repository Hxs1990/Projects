#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "expression.h"
#include "BinOp.h"
#include "UnOp.h"
#include "LoneInts.h"
#include "Variables.h"
using namespace std;

// You will need to make changes to this file
int main () {
  string s;
  vector<Expression*> stack;
  Expression *result = nullptr;
  // Read and construct expression object
  while (cin >> s) {
    istringstream ss(s);
    int n;
    if (ss >> n) {
	// Pushes a LoneInt object to the back of the stack
      stack.emplace_back(new LoneInts(n));
    }
    else if (s == "NEG" || s == "ABS") {
      if (stack.size()){
	  // Only runs if there's at least 1 thing in the stack
	  // Pops the top and assigns that as the expression the UnOp object points to
	  //  and then is pushed on the stack
        Expression *trest = stack.back();
        stack.pop_back();
        stack.emplace_back(new UnOp(trest, s));
      }
    }
    else if (s == "+" || s == "-" || s == "*" || s == "/") {
      if (stack.size() >= 2){
	  // Only runs if there's at least 2 things in the stack
	  // Pops 2 expressions and is assigned to be a newly created
	  //  BinOp's left and right expressions respectively
	  // and then is pushed on the stack.
        Expression *tright = stack.back();
        stack.pop_back();
        Expression *tleft = stack.back();
        stack.pop_back();
        stack.emplace_back(new BinOp(tleft,tright,s));
      }
    }
	// Stores the result from the stack and terminates the loop
    else if (s == "done") {
      result = stack.back();
      break;
    }
	// Pushes a new variable to the stack
    else {
      stack.emplace_back(new Variables(s));
    }
  }
  if(!cin.eof()){ 
    cout << result->prettyprint();
    cout << endl;
  }

  // Command interpreter
  while (cin >> s) {
    string input;
    int n;
	// Evaluates the expression
    if (s == "eval") {
      try{
         cout << result->evaluate();
      }
	  // Throws an exception when there exists an unset variable
      catch(UnsetVariable &e){
      cout << e.what() << " has no value.";
      }
      cout << endl;
    }
	// Sets variable to a given value
    else if (s == "set") {
      cin >> input;
      cin >> n;
      result->set(input,n);
    }
	// Unsets variable
    else if (s == "unset") {
      cin >> input;
      result->unset(input);
    }
	// Prints the expression
    else if (s == "print") {
      cout << result->prettyprint();
      cout << endl;
    }
	// Copy the expression (does not change the original expression)
	// The copied expression then has all x variables set to 1 and then
	// evalated and then deleted.
    else if (s == "copy"){
      Expression *theCopy = result->duplicate();
      cout << theCopy->prettyprint() << endl;
      theCopy->set("x", 1);
      cout << theCopy->prettyprint() << endl;;
      try{
        cout << theCopy->evaluate() << endl;
      }
      catch(UnsetVariable &e){
        cout  << e.what() << " has no value.";
        cout <<endl;
      }

      delete theCopy;
    }
  }
  delete result;
}

