#include <vector>
#include <iostream>
#include "grid.h"
#include "textdisplay.h"
#include "cell.h"
#include "subject.h"
#include "graphicsdisplay.h"

Grid::~Grid(){
	delete td;
	delete ob;
}

// Sets up the observers for each cell in the grid, where ob is
// for the graphical observer
void Grid::setObserver(Observer<Info, State> *ob){
	int length = theGrid.size();
	td = new TextDisplay{length};

	for(auto& rows : theGrid){
		for(auto& cells: rows){
			ob->notify(cells);
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

//Determine who the winner is by comparing Black to White
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

// Creates a grid with size n
void Grid::init(size_t n){
	delete td;
	delete ob;
	theGrid.clear();

	// Loop to create the actual cell
	for(size_t r = 0; r < n; ++r){
		std::vector<Cell> aRow;
		for(size_t c = 0; c < n; ++c){
			aRow.emplace_back(Cell{r,c});
		}
		theGrid.emplace_back(aRow);
	}
	// Setting up the 4 center pieces
	theGrid[n/2 - 1][n/2 - 1].setPiece(Colour::Black);
	theGrid[n/2][n/2].setPiece(Colour::Black);
	theGrid[n/2 - 1][n/2].setPiece(Colour::White);
	theGrid[n/2][n/2 - 1].setPiece(Colour::White);
	int length = n;
	ob = new GraphicsDisplay{length,500};
	setObserver(ob);
}

// Sets a piece on the grid. Checks for the out of bounds and notifies the neighbours
//  when a piece is placed.
void Grid::setPiece(size_t r, size_t c, Colour colour){
	if (r > theGrid.size() || c > theGrid.size()) throw InvalidMove{};
	else if (theGrid[r][c].getInfo().colour == Colour::None){
		theGrid[r][c].setPiece(colour);
		int length= theGrid.size(); 
		for(int i = 0; i < length; ++i){
			for (int j = 0; j <length; ++j){
				td->notify(theGrid[i][j]);
			}
		}
	}
	else{
		throw InvalidMove{};
	}
}

// changed the colour of the specified piece
void Grid::toggle(size_t r, size_t c){
	if (theGrid[r][c].getInfo().colour != Colour::None){
		theGrid[r][c].toggle();
		td->notify(theGrid[r][c]); 
	}
}

// Outputs the grid
std::ostream& operator<<(std::ostream &out, const Grid &g){
	out << *g.td;
	return out;
}









