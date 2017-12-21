//william chan - wcy2chan - september 2017

#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string encrypt(const string direction, int shift){
	/* encrypt() shifts each char in a newline terminated string 
		to the given direction by shift units. */
	string input;
	getline(cin,input);

	// Negate the shift value if left (opposed to right).
	if (direction == "left"){
		shift = -shift;
	}

	/* Go through the string and shift each character the
		given direction and distance if it is a letter in
		the alphabet.
		Does not shift non-alphabet letters. */
	for (unsigned int i = 0; i < input.length(); ++i){
		/* shifted determines if the supposed shifted char 
			is out of bounds or not. 
			(shifted is int type to surpass the char size limits
			 while maintaing the ability to compare chars)*/
		// length is the number of alphabet characters
		int shifted = input[i] + shift;
		const int length = 26;

		if('A' <= input[i] && input[i] <= 'Z'){
			// If greater than Z, wrap around back to A
			if (shifted > 'Z'){
				input[i] -= (length - shift);
			}
			// If smaller than A, wrap around back to Z
			if (shifted < 'A'){
				input[i] += (length + shift);
			} 
			// Keep the shifted value if within range
			if ('A' <= shifted && 'Z' >= shifted){
				input[i] = shifted;
			}
		}

		// Similar case as above but for lowercase
		else if ('a' <= input[i] && input[i] <= 'z'){
			if (shifted > 'z'){
				input[i] -= (length - shift);
			}
			if (shifted < 'a'){
				input[i] += (length + shift);
			}
			if ('a' <= shifted && 'z' >= shifted){
				input[i] = shifted;
			}
		}

	}
	return input;
}

void errMsg(){
	// Displays an Error message to cerr
	cerr << "ERROR" << endl; 
}

int main(int argc, char *argv[]){
	// If more than 3 args passed, runs errMsg and quits.
	if (argc >= 4){
		errMsg();
		return(1);
	}

	// Default settings for 0 arguments passed
	string direction = "right";
	string opDirection = "left";
	int shift = 3;

	// If there are 1 or 2 arguments
	if (argc == 2 || argc == 3){
		/* Alters default values to match the programs design to shift from
		0-25 right/left depending on 1 or 2 args */
		string shiftString = argv[1];
		istringstream iss{shiftString};
		int n;

		/* Checks if n was an integer and within the programs 0-25 range
		regardless if it was ran with 1 or 2 args.
		Does an additional check if 2 arguments exist and are valid*/
		if (iss >> n && 0 <= n && n <= 25){
			shift = n;
		} else{
			errMsg();
			return(1);
		}

		// Second check for 2 args
		if (argc == 3){
			direction = argv[2];
			// Switch directions if user specified left direction
			if (direction == "right" || direction == "left"){
				if (direction == "left"){
					opDirection = "right";
				}
			} else{
				errMsg();
				return(1);
			}
		}
	}


	// Main loop.
	// Reads until EOF or 'q', looping the user for input to encrypt or decrypt.
	while(true){
		char input;
		cin >> input;
		if (cin.eof()) return 0;
		switch(input){
			case 'e':
				cout << encrypt(direction, shift) << endl;
				break;
			case 'd':
				cout << encrypt(opDirection, shift) << endl;
				break;
			case 'q':
				return 0;
			}
	}
}


