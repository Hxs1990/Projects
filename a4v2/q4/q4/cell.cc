#include "cell.h"
#include "state.h"
#include "subject.h"
#include "grid.h"
#include "textdisplay.h"
#include <iostream>
Cell::Cell(size_t r, size_t c):r{r},c{c}{}

// Updates the colour of the cell and notifies all the neighbours around that cell
//  by changing this cell's statetype to a NewPiece
//  (Direction doesnt matter in this case)
void Cell::setPiece(Colour colour){
	this->colour = colour;
	State newState{StateType::NewPiece,colour,Direction::N};
	setState(newState);
	notifyObservers();
}

//Changes the colour
void Cell::toggle(){
	if (colour == Colour::Black){
		colour = Colour::White;
	}
	else{
		colour = Colour::Black;
	}
}

//Returns an Info structure containing all the details of cell 
// at the time getInfo() was called
Info Cell::getInfo() const{
	Info cellInfo{r,c,colour};
	return cellInfo;
}

// Helper function for notify()
// Checks if given a direction, the info of the whoFrom piece wF, and the
// info from the current piece, checks to see if the current piece is the
// specified direction away from the wF piece. Returns true if it is.
bool isInline(Direction d, Info wF, Info cur){
	if (d == Direction::N){
		if (wF.col == cur.col &&
			wF.row == cur.row + 1) return true;
	}
	else if (d == Direction::NE){
		if (wF.col + 1 == cur.col &&
			wF.row == cur.row + 1) return true;
	}
	else if (d == Direction::E){
		if (wF.col + 1 == cur.col &&
			wF.row == cur.row) return true;
	}
	else if (d == Direction::SE){
		if (wF.col + 1 == cur.col &&
			wF.row + 1 == cur.row) return true;
	}
	else if (d == Direction::S){
		if (wF.col == cur.col &&
			wF.row + 1 == cur.row) return true;
	}
	else if (d == Direction::SW){
		if (wF.col == cur.col + 1 &&
			wF.row + 1 == cur.row ) return true;
	}
	else if (d == Direction::W){
		if (wF.col == cur.col + 1 &&
			wF.row == cur.row) return true;
	}
	else if(d == Direction::NW){
		if (wF.col == cur.col + 1 &&
			wF.row == cur.row + 1) return true;
	}
	return false;
}

void Cell::notify(Subject<Info, State> &whoFrom){
	StateType t = whoFrom.getState().type;
	Colour c = whoFrom.getState().colour;
	Direction d = whoFrom.getState().direction;
	Info wF = whoFrom.getInfo();
	// Check if it's a newpiece call
	if (t == StateType::NewPiece){

		if (colour != Colour::None && colour != c){
			size_t newR = getInfo().row;
			size_t newC = getInfo().col;
			size_t rw = whoFrom.getInfo().row;
			size_t cl = whoFrom.getInfo().col;
			State relay{StateType::Relay,c,Direction::N};
			//determine location of the new piece respective to
			// the current piece that was its neighbour
			if (newR < rw && newC < cl){
				relay.direction = Direction::NW;
			}
			else if (newR > rw && newC > cl){
				relay.direction = Direction::SE;
			}
			else if (newR < rw && newC > cl){
				relay.direction = Direction::NE;
			}
			else if (newR > rw && newC < cl){
				relay.direction = Direction::SW;
			}
			else if (newR == rw && newC > cl){
				relay.direction = Direction::E;
			}
			else if (newR == rw && newC < cl){
				relay.direction = Direction::W;
			}
			else if (newR < rw && newC == cl){
				relay.direction = Direction::N;
			}
			else{
				relay.direction = Direction::S;
			}
			//Now we relay that information to our other neighbours
			setState(relay);
			notifyObservers();
		}
	}
	// Check to see if it was a Relay
	else if (t == StateType::Relay){
		// If it's a different colour, notify our neighbours
		//  if the piece isInline with the original newpiece
		// If it isn't then do nothing.
		if (colour != Colour::None && colour != c){
			if (isInline(d,wF,getInfo())){
				setState(whoFrom.getState());
				notifyObservers();
			}
		}
		// If we hit a piece that matches the colour of the new piece
		else if (colour != Colour::None && colour == c){
			// If it's inline then we reverse the direction and notify back
			if (isInline(d,wF,getInfo())){
				State reply{StateType::Reply,c,Direction::N};
				if (d == Direction::N){
					reply.direction = Direction::S;
				}
				else if (d == Direction::NE){
					reply.direction = Direction::SW;
				}
				else if (d == Direction::E){
					reply.direction = Direction::W;
				}
				else if (d == Direction::SE){
					reply.direction = Direction::NW;
				}
				else if (d == Direction::S){
					reply.direction = Direction::N;
				}
				else if (d == Direction::SW){
					reply.direction = Direction::NE;
				}
				else if (d == Direction::W){
					reply.direction = Direction::E;
				}
				else if (d == Direction::NW){
					reply.direction = Direction::SE;
				}
				// Notify as a Reply to trigger the pieces to toggle
				setState(reply);
				notifyObservers();
			}
		}
	}
	// Check if it was a Reply
	else if (t == StateType::Reply){
		// If the colour doesn't match, then keep sending the replay back
		//  inLine and toggle the colour too.
		if (colour != Colour::None && colour != c){
			if (isInline(d,wF,getInfo())){
				toggle();
				setState(whoFrom.getState());
				notifyObservers();
			}
		}
	}
}

