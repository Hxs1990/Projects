#include "cell.h"
#include "state.h"
#include "subject.h"
#include "grid.h"
#include "textdisplay.h"
#include <iostream>
Cell::Cell(size_t r, size_t c):r{r},c{c}{}

void Cell::setPiece(Colour colour){
	this->colour = colour;
	State newState{StateType::NewPiece,colour,Direction::N};
	setState(newState);
	notifyObservers();
}

void Cell::toggle(){
	if (colour == Colour::Black){
		colour = Colour::White;
	}
	else{
		colour = Colour::Black;
	}
}

Info Cell::getInfo() const{
	Info cellInfo{r,c,colour};
	return cellInfo;
}

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
	//Lets check if it's a new piece
	StateType t = whoFrom.getState().type;
	Colour c = whoFrom.getState().colour;
	Direction d = whoFrom.getState().direction;
	Info wF = whoFrom.getInfo();
	if (t == StateType::NewPiece){

		if (colour != Colour::None && colour != c){
			size_t newR = getInfo().row;
			size_t newC = getInfo().col;
			size_t rw = whoFrom.getInfo().row;
			size_t cl = whoFrom.getInfo().col;
			State relay{StateType::Relay,c,Direction::N};
			//determine location
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
			setState(relay);
			notifyObservers();
		}
	}
	else if (t == StateType::Relay){
		if (colour != Colour::None && colour != c){
			if (isInline(d,wF,getInfo())){
				setState(whoFrom.getState());
				notifyObservers();
			}
		}
		else if (colour != Colour::None && colour == c){
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
				setState(reply);
				notifyObservers();
			}
		}
	}
	
	else if (t == StateType::Reply){
		if (colour != Colour::None && colour != c){
			if (isInline(d,wF,getInfo())){
				toggle();
				setState(whoFrom.getState());
				notifyObservers();
			}
		}
	}
}

