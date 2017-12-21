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
	// Place at the back at the stack if it's just an Int
    if (ss >> n) {
      stack.emplace_back(new LoneInts(n));
    }
	// Pop the stack and place an UnOp in the stack pointing to the popped item
    else if (s == "NEG" || s == "ABS") {
      if (stack.size()){
        Expression *trest = stack.back();
        stack.pop_back();
        stack.emplace_back(new UnOp(trest, s));
      }
    }
	// Pop two things in the stack and place an BinOp in the stack pointing to the 2 popped items
    else if (s == "+" || s == "-" || s == "*" || s == "/") {
      if (stack.size() >= 2){
        Expression *tright = stack.back();
        stack.pop_back();
        Expression *tleft = stack.back();
        stack.pop_back();
        stack.emplace_back(new BinOp(tleft,tright,s));
      }
    }
	// Terminates the loop and result is set
    else if (s == "done") {
      result = stack.back();
      break;
    }
	// Variable are created and placed in the stack
    else {
      stack.emplace_back(new Variables(s));
    }
  }
  // Prints the expression when there is no more input
  if(!cin.eof()){ 
    cout << result->prettyprint();
    cout << endl;
  }

  // Command interpreter
  while (cin >> s) {
    string input;
    int n;
    if (s == "eval") {
	// Throws an UnsetVariable error if the variable is unset
      try{
         cout << result->evaluate();
      }
      catch(UnsetVariable &e){
        cout  << "UnsetVariable: "+e.what();
      }
      cout << endl;
    }
	// sets the variable to the given int
    else if (s == "set") {
      cin >> input;
      cin >> n;
      result->set(input,n);
    }
	// unsets the variable to have no value set
    else if (s == "unset") {
      cin >> input;
      result->unset(input);
    }
	// prints out the expression
    else if (s == "print") {
      cout << result->prettyprint();
      cout << endl;
    }
  }
  delete result;
}

