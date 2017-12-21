// william chan - wcy2chan - september 2017
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

void invalid(){
	cerr << "wordWrap: invalid usage" << endl;
	cerr << "Usage: wordWrap [-w textWidth] [-l|-c|-r]" <<  endl;
}

void wordWrapLeft(int width){
	string output;
	string word;
	ostringstream s{output};

	// Loops through until EOF while reading in new words and building
	//	a new line. If the line is over the width, then stream the line
	//	to the output and create a new line and put the new word there.
	// No padding is done for left jusitification
	while(true){
		cin >> word;
		// If there is no more input, check to see if we are still 
		//	building a new line or not. If we are send it stream. Then break.
		if (cin.eof()){
			if (!output.empty()){
				s << output<< endl;
			}
			break;
		}
		int len = word.length();
		int outputLen = output.length();

		// Case where start of new line and the word is smaller than width
		if (output.empty() && (len + outputLen < width)){
			output = word;
		}
		// Case where start of new line and word is equal to the width
		else if (output.empty() && (len + outputLen == width)){
			output = word;
			s << output << endl;
			output.clear();
		}
		// Case where line is still smaller than width when word is
		//	appended to the line with a space.
		else if (len + outputLen + 1 < width ){
			output = output + ' ' + word;
		}
		// Case where line is equal to width when word is appended
		//	to the line with a space
		else if (len + outputLen + 1 == width){
			output = output + ' ' + word;
			s << output << endl;
			output.clear();
		}
		else{ // Case where word was bigger than width when appended
			if (len > width){
				if (!output.empty()){
					s << output << endl;
				}
				output.clear();
				outputLen = 0;
				// This loop splits up the word into new lines if needed
				for(int i = 0; i < len; ++i){
					output += word[i];
					outputLen++;
					if (outputLen == width){
						s << output << endl;
						outputLen = 0;
						output.clear();
					}
				}
			}
			// Case where word couldn't fit current line but can
			//	fit in a new line
			else{
				s << output << endl;
				output.clear();
				output = word;
			}
		}
	}
	cout << s.str();
}

void wordWrapRight(int width){
	string output;
	string word;
	ostringstream s{output};

	// Loops through until EOF while reading in new words and building
	//	a new line. If the line is over the width, then stream the line
	//	to the output and create a new line and put the new word there.
	// Padding is equal to the width provided by the user.
	while(true){
		cin >> word;
		// If there is no more input, check to see if we are still 
		//	building a new line or not. If we are send it stream. Then break.
		if (cin.eof()){
			if (!output.empty()){
				s << setw(width) << output<< endl;
			}
			break;
		}
		int len = word.length();
		int outputLen = output.length();

		// Case where start of new line and the word is smaller than width
		if (output.empty() && len + outputLen < width){
			output = word;

		}
		// Case where start of new line and word is equal to the width
		else if (output.empty() && len + outputLen == width){
			output = word;
			s << output << endl;
			output.clear();
		}
		// Case where line is still smaller than width when word is
		//	appended to the line with a space.
		else if (len + outputLen + 1 < width ){
			output = output + ' ' + word;
		}
		// Case where line is equal to width when word is appended
		//	to the line with a space
		else if (len + outputLen + 1== width){
			output = output + ' ' + word;
			s << output << endl;
			output.clear();

		}
		else{  // Case where word was bigger than width when appended
			if (len > width){
				if (!output.empty()){
				s << setw(width) << output << endl;
				}
				output.clear();
				outputLen = 0;
				// This loop splits up the word into new lines if needed
				for(int i = 0; i < len; ++i){
					output += word[i];
					outputLen++;
					if (outputLen == width){
						s << setw(width) << output << endl;
						outputLen = 0;
						output.clear();
					}
				}
			}
			// Case where word couldn't fit current line but can
			//	fit in a new line
			else{
				s << setw(width) << output << endl;
				output.clear();
				output = word;
			}
		}
	}
	cout << s.str();
}

void wordWrapCenter(int width){ // 10
	string output; // there
	string word; // there
	ostringstream s{output}; // 
	int outputLen = 0; // 5

	// Loops through until EOF while reading in new words and building
	//	a new line. If the line is over the width, then stream the line
	//	to the output and create a new line and put the new word there.
	// Padding is equal to the length of line averaged with the given width.
	while(true){
		cin >> word; 

		int len = word.length(); 
		outputLen = output.length(); 
		if (cin.eof()){
			if (!output.empty()){
				s << setw((outputLen + width)/2) << output<< endl;
			}
			break;
		}
		if (output.empty() && len + outputLen < width){ 
		//start of a new line and the word is smaller than margin
			output = word;

		}
		else if (output.empty() && len + outputLen == width){
		//start of a new line and the word is exactly the margin
			output = word;
			s << output << endl;
			output.clear();
		}
		else if (len + outputLen + 1 < width ){
		// appendable to the current output line
			output = output + ' ' + word;
		}
		else if (len + outputLen + 1 == width){
		// appendable to the current output line
		// must calculate the margin and send line to ostringstream
			output = output + ' ' + word;
			s << output << endl;
			output.clear();
		}
		else{ // word was bigger than width
			if (len > width){ // the word if bigger than the margin
				// must break up word accordingly
				if (!output.empty()){
				s << setw((outputLen + width) / 2) << output << endl;
				}
				output.clear();
				outputLen = 0;
				for(int i = 0; i < len; ++i){
					output += word[i];
					outputLen++;
					if (outputLen == width){
						s << setw(width) << output << endl;
						outputLen = 0;
						output.clear();
					}
				}
			}
			else{
				s << setw((outputLen+width)/2) << output << endl;
				output.clear();
				output = word;
			}
		}
	}
	cout << s.str();
}

int main(int argc, char* argv[]){
	// if argc has values that are not 1 or 3 or 4, invalid.
	if (!(argc == 1 || argc == 4 || argc == 3)){ 
		invalid(); 
		return 1;
	}

	// default values
	string wFlag = "-w";
	string textWidthFlag;
	string dirFlag = "-l";
	int textWidth = 25;

	/* If the program was ran with 2 parameters, check to see
		if they were valid. */
	if (argc == 3){
		wFlag = argv[1];
		textWidthFlag = argv[2];

		istringstream iss{textWidthFlag};
		if (!(iss >> textWidth) || wFlag != "-w" || textWidth < 1){
			invalid();
			return 1;
		}
	}
	/* If the program was ran with 3 parameters, check to see
		if they were valid.*/
	if (argc == 4){
		wFlag = argv[1];
		textWidthFlag = argv[2];
		dirFlag = argv[3];
		
		istringstream iss{textWidthFlag};
		if (!(iss >> textWidth) || wFlag != "-w" ||
			(dirFlag != "-l" && dirFlag != "-c" && dirFlag != "-r") || textWidth < 1) {
			invalid();
			return 1;
		}
	}
	// Run the user specified wordWrap
	if (dirFlag == "-l"){
		wordWrapLeft(textWidth);
	}
	else if (dirFlag == "-r"){
		wordWrapRight(textWidth);
	} else{
		wordWrapCenter(textWidth);
	}
	return 0;

}


