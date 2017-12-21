#include <vector>
#include "textdisplay.h"
#include <iostream>
#include "subject.h"

//Creates a TextDisplay representation of the Grid
TextDisplay::TextDisplay(int n):theDisplay{},gridSize{n}{
	for(int r = 0; r < gridSize; ++r){
		std::vector<char> row;
		for(int c= 0; c < gridSize; ++c){
			row.emplace_back('-');
		}
		theDisplay.emplace_back(row);
	}
	theDisplay[n/2 - 1][n/2 - 1] = 'B';
	theDisplay[n/2][n/2] = 'B';
	theDisplay[n/2 - 1][n/2] = 'W';
	theDisplay[n/2][n/2 - 1] = 'W';
}

// Notifies the TextDisplay representation to update itself based
//  on the new colour changes
void TextDisplay::notify(Subject<Info, State> &whoNotified){
	size_t r = whoNotified.getInfo().row;
	size_t c = whoNotified.getInfo().col;
	if (whoNotified.getInfo().colour == Colour::White){
		theDisplay[r][c] = 'W';
	}
	else if (whoNotified.getInfo().colour == Colour::Black){
		theDisplay[r][c] = 'B';
	}
}

// Outputs the text representation of the grid;
std::ostream& operator<<(std::ostream &out, const TextDisplay &td){
	for(auto rows: td.theDisplay){
		for(auto cells: rows){
			out << cells;
		}
		out << std::endl;
	}
	return out;
}

