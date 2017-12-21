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
    while (true) {
      cin >> cmd;
      if (cin.eof()) break;

      if (cmd == "new") {
	  	// Game has started
	  	started = true;
		// Black goes first
        turn = Colour::Black;
        int n;
        cin >> n;
		// Setting up the board
        g.init(n);
		g.setObserver(nullptr);
        cout << g;
      }
      else if (cmd == "play") {
	  // Only play if the grid as been started
	  if (started){
        int r = 0, c = 0;
        cin >> r >> c;
        try{
          g.setPiece(r,c,turn); 
        }
        catch(InvalidMove&){
          continue;
        }
		// print result of the move
        cout << g;

		// change turn
        if(turn == Colour::Black){
          turn = Colour::White;
        }
        else{
          turn = Colour::Black;
        }
        
		// Checks if the grid is full and determines the winner
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
