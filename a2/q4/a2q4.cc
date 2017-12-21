// william chan - wcy2chan - september 2017
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

// counts the decimal place; used for formatting
static int dplace(int x){
	int count = 0;
	while(x != 0){
		x = x/10;
		count++;
	}
	return count;
}

int wordsInLine(const string &line){
	//ignores beginning whitespace, and counts 
	int count = 0;
	int len = line.length();
	int pos = 0;
	bool whitespace = true;
	// first loop finds the first non-whitespace
	//  and starts the program there.
	for (int i = 0; i < len; ++i){
		if (line[i] != ' ' && line[i] != 9){
			break;
		}
		pos++;
	}
	// whitespace is used to distingush if a word exists compared
	//   to just if it was duplicate white spaces in a row.
	for (int i = pos; i < len; ++i){
		if ((line[i] != ' ' && line[i] != 9) && whitespace){
			count++;
			whitespace = false;
		}
		else if((line[i] == ' ' && line[i] != 9) && !whitespace){
			whitespace = true;
		}
	}
	return count;
}

int charsInLine(const string &line){
	// the plus one is for the unaccounted newline character that
	//  gets trimmed off when getline uses it as a delimiter
	return line.length()+1;
} 

void printData(bool l, bool w, bool c, int lines, int words, int chars, 
	const string filename = ""){
	//formats the strings to left with extra padding of 5;
	//  prints them out as LINES WORDS CHARS (optional filename)
	//function can be called with a filename and will be displayed within 
	//   the new line.

	int nameLength = filename.length();

	if (l && w && c){
		cout << setw(dplace(lines) + 5) << left << lines 
		 	 << setw(dplace(words) + 5) << left << words
		 	 << setw(dplace(chars) + 5) << left << chars 
		 	 << setw(nameLength + 5) << left << filename << endl;
	}
	else if (l && w){
		cout << setw(dplace(lines) + 5) << left << lines
		     << setw(dplace(words) + 5) << left << words
		     << setw(dplace(chars) + 5) << left << ' ' 
		     << setw(nameLength + 5) << left << filename << endl;
	}
	else if (l && c){
		cout << setw(dplace(lines) + 5) << left << lines
		     << setw(dplace(words) + 5) << left << ' '
		     << setw(dplace(chars) + 5) << left << chars 	
		     << setw(nameLength + 5) << left << filename << endl;
	}
	else if (w && c){
		cout << setw(dplace(lines) + 5) << left << ' '
		     << setw(dplace(words) + 5) << left << words
		     << setw(dplace(chars) + 5) << left << chars 
		     << setw(nameLength + 5) << left << filename << endl;
	}
	else if (c){
		cout << setw(dplace(lines) + 5) << left << ' '
		     << setw(dplace(words) + 5) << left << ' '
		     << setw(dplace(chars) + 5) << left << chars 
		     << setw(nameLength + 5) << left << filename << endl;	
	}
	else if (w){
		cout << setw(dplace(lines) + 5) << left << ' '
		     << setw(dplace(words) + 5) << left << words
		     << setw(dplace(chars) + 5) << left << ' ' 
		     << setw(nameLength + 5) << left << filename << endl;	
	}
	else if (l){
		cout << setw(dplace(lines) + 5) << left << lines
		     << setw(dplace(words) + 5) << left << ' '
		     << setw(dplace(chars) + 5) << left << ' ' 	
		     << setw(nameLength + 5) << left << filename << endl;
	}
}

int main(int argc, char *argv[]){
	// program iterates through standard input or given files
	//  and counts the number of chars, words, and/or lines.
	bool checkLines = false;
	bool checkWords = false;
	bool checkChars = false;
	bool noFiles = true;
	bool noFlags = true;

	int lines, words, chars;
	lines = words = chars = 0;


	// All three flags are set to true if program is ran with no arguments
	if (argc == 1){
		checkLines = checkWords = checkChars = true;
	}
	else{
		// this loop is to turn on the proper read settings
		for (int i = 1; i < argc; ++i){
			// check through the argv array
			string arg = argv[i];
			if (arg[0] == '-'){
				// if a potential - flag is found, parse through it
				int len = arg.length();
				for (int k = 1; k < len; ++k ){
					if (arg[k] == 'w'){
						checkWords = true;
					}
					else if (arg[k] == 'l'){
						checkLines = true;
					}
					else{
						checkChars = true;
					}
				}
				noFlags = false;
			}
			else {
				//if it doesn't contain a - flag, then it must be a file
				noFiles = false;
			}
		}

	}

	// if no flags were found, program sets all three flags to true
	if (argc != 1 && noFlags){
		checkLines = checkWords = checkChars = true;
	}

	// Either reads from input or from files depending on if there are noFiles
	if (noFiles){
		/* Read and count each line encountered, then store it as a stringstream.
		Then reads and counts each word in the line with cin from stringstream.
		Then counts each character in the line with gcount from stringstream.
		Then prints it out*/
		while(true){
			string line;
			if(!getline(cin,line)) break;
			lines++;
			words += wordsInLine(line);
			chars += charsInLine(line);
		}
		printData(checkLines,checkWords,checkChars,lines,words,chars);
	}
	else{
		/* This means that there exists one or more files that need to be read 
		A for loop checks through the arguments again and reads and calculated
		all of them. Then prints out the results for each file and then a total*/
		int numOfFiles = 0;
		for( int i = 1; i < argc; ++i ){
			//if a file is found loop through it's contents and compute
			//  the required data.
			if (argv[i][0] != '-'){
				numOfFiles++;
				string filename = argv[i];
				ifstream file{filename};
				int filelines = 0;
				int filewords = 0;
				int filechars = 0;
				while(true){
					string line;
					if (!getline(file,line)) break;
					filelines++;
					filewords += wordsInLine(line);
					filechars += charsInLine(line);
				}
				printData(checkLines,checkWords,checkChars,filelines,filewords,filechars,filename);
	    	 	lines += filelines;
	    	 	words += filewords;
	    	 	chars += filechars;
			}
		}
		// prints out a total if there was more than 1 file provided
		if (numOfFiles > 1) {
		printData(checkLines,checkWords,checkChars,lines,words,chars,"total");
		}
	}
}

