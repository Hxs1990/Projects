#include <vector>
#include <iostream>
#include "grid.h"
#include "textdisplay.h"
#include "cell.h"
#include "subject.h"
Grid::~Grid(){
// LOOK OVER
	delete td;
	delete ob;
}

void Grid::setObserver(Observer<Info, State> *ob){
	//TO DO
}

bool Grid::isFull() const{
	for(auto rows: theGrid){
		for(auto cells: rows){
			// immediately returns false if a cell has no colour
			if (cells.getInfo().colour == Colour::None) return false;
		}
	}
	// Finished checking through every row in the grid
	//  and every cell is either black or white.
	return true;
}

Colour Grid::whoWon() const{
	int blackScore = 0;
	int whiteScore = 0;
	for(auto rows: theGrid){
		for(auto cells: rows){
			cells.getInfo().colour == Colour::White ? ++whiteScore : ++blackScore;
		}
	}
	if (blackScore > whiteScore) return Colour::Black;
	if (blackScore == whiteScore) return Colour::None;
	return Colour::White;
}

void Grid::init(size_t n){
	delete td;
	delete ob;
	theGrid.clear();
	for(size_t r = 0; r < n; ++r){
		std::vector<Cell> aRow;
		for(size_t c = 0; c < n; ++c){
			aRow.emplace_back(Cell{r,c});
		}
		theGrid.emplace_back(aRow);
	}
	theGrid[n/2 - 1][n/2 - 1].setPiece(Colour::Black);
	theGrid[n/2][n/2].setPiece(Colour::Black);
	theGrid[n/2 - 1][n/2].setPiece(Colour::White);
	theGrid[n/2][n/2 - 1].setPiece(Colour::White);
	int length = n;
	td = new TextDisplay{length};

	for(auto& rows : theGrid){
		for(auto& cells: rows){
			int r = cells.getInfo().row;
			int c = cells.getInfo().col;
			for(int i = r - 1; i <= r + 1; ++i){
				for(int j = c - 1; j <= c + 1; ++j){
					if (i < 0 || j < 0 || i > length-1 || j > length-1){
						continue;
					}
					if (i == r && j == c){
						continue;
					}
					cells.attach(&theGrid[i][j]);
				}
			}
		}
	}
}

void Grid::setPiece(size_t r, size_t c, Colour colour){
	if (r > theGrid.size() || c > theGrid.size()) throw InvalidMove{};
	if (theGrid[r][c].getInfo().colour == Colour::None){
		theGrid[r][c].setPiece(colour);
		for(int i = 0; i < theGrid.size(); ++i){
			for (int j = 0; j <theGrid.size(); ++j){
				td->notify(theGrid[i][j]);
			}
		}
	}
	else{
		throw InvalidMove{};
	}
}

void Grid::toggle(size_t r, size_t c){
	if (theGrid[r][c].getInfo().colour != Colour::None){
		theGrid[r][c].toggle();
		td->notify(theGrid[r][c]); 
	}
}

std::ostream& operator<<(std::ostream &out, const Grid &g){
	out << *g.td;
	return out;
}









