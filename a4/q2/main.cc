#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "expression.h"
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
      stack.emplace_back(new LoneInts(n));
    }
    else if (s == "NEG" || s == "ABS") {
      if (stack.size()){
        Expression *trest = stack.back();
        stack.pop_back();
        stack.emplace_back(new UnOp(trest, s));
      }
    }
    else if (s == "+" || s == "-" || s == "*" || s == "/") {
      if (stack.size() >= 2){
        Expression *tright = stack.back();
        stack.pop_back();
        Expression *tleft = stack.back();
        stack.pop_back();
        stack.emplace_back(new BinOp(tleft,tright,s));
      }
    }
    else if (s == "done") {
      result = stack.back();
      break;
    }
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
    if (s == "eval") {
      try{
         cout << result->evaluate();
      }
      catch(string e){
        cout << e;
      }
      cout << endl;
    }

    else if (s == "set") {
      cin >> input;
      cin >> n;
      result->set(input,n);
    }
    else if (s == "unset") {
      cin >> input;
      result->unset(input);
    }
    else if (s == "print") {
      cout << result->prettyprint();
      cout << endl;
    }
    else if (s == "copy"){
      Expression *theCopy = result->duplicate();
      cout << theCopy->prettyprint() << endl;
      theCopy->set("x", 1);
      cout << theCopy->prettyprint() << endl;;
      try{
        cout << theCopy->evaluate() << endl;
      }
      catch(string e){
        cout << e;
        cout <<endl;
      }

      delete theCopy;
    }
  }
}
