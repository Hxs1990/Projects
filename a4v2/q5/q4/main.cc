#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
#include "graphicsdisplay.h"
#include "subject.h"
#include "observer.h"
#include "textdisplay.h"

using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;
  bool started = false;

  Colour turn;
  try {
  	// Enter game loop
    while (true) {
      cin >> cmd;
      if (cin.eof()) break;

	 
      if (cmd == "new") {
		started = true; // Prevents premature plays from happening
       	turn = Colour::Black;
       	int n;
       	cin >> n;		
       	g.init(n);
		cout << g;
	  }
      else if (cmd == "play") {
	  	if (started){
        	int r = 0, c = 0;
        	cin >> r >> c;
          try{
          	g.setPiece(r,c,turn); 
          }
          catch(InvalidMove&){
            continue;
          }

		// Output grid and switch the current turn
        cout << g;
        if(turn == Colour::Black){
          turn = Colour::White;
        }
        else{
          turn = Colour::Black;
        }
       // If grid is full, determine who wins
        if(g.isFull()){
          	if(g.whoWon() == Colour::White){
            	cout << "White Wins!" << endl;
          	}
         	 else if (g.whoWon() == Colour::Black){
            	cout << "Black Wins!" << endl;
          	}
          	else{
            	cout << "Tie!" << endl;
          	}
         	 break;
		  }
      	}
	  }
    }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
