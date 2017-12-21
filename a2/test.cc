// william chan - wcy2chan - september 2017
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

void invalid(){
	cout << "wordWrap: invalid usage" << endl;
	cout << "Usage: wordWrap [-w textWidth] [-l|-c|-r]" <<  endl;
	exit(1);
}

void wordWrapLeft(int width){
	string output;
	string word;
	ostringstream s{output};

	while(true){
		cin >> word;
		if (cin.eof()){
			if (!output.empty()){
				s << output<< endl;
			}
			break;
		}
		int len = word.length();
		int outputLen = output.length();

		if (output.empty() && (len + outputLen < width)){
			output = word;
		}
		else if (output.empty() && (len + outputLen == width)){
			output = word;
			s << output << endl;
			output.clear();
		}
		else if (len + outputLen + 1 < width ){
			output = output + ' ' + word;
		}
		else if (len + outputLen + 1 == width){
			output = output + ' ' + word;
			s << output << endl;
			output.clear();
		}
		else{ // word was bigger than width
			if (len > width){
				if (!output.empty()){
					s << output << endl;
				}
				output.clear();
				int x = 0;
				for(int i = 0; i < len; ++i){
					output += word[i];
					x++;
					if (x == width){
						s << output << endl;
						x = 0;
						output.clear();
					}
				}
			}
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

	while(true){
		cin >> word;
		if (cin.eof()){
			if (!output.empty()){
				s << setw(width) << output<< endl;
			}
			break;
		}
		int len = word.length();
		int outputLen = output.length();

		if (output.empty() && len + outputLen < width){
			output = word;

		}
		else if (output.empty() && len + outputLen == width){
			output = word;
			s << output << endl;
			output.clear();
		}
		else if (len + outputLen + 1 < width ){
			output = output + ' ' + word;
		}
		else if (len + outputLen + 1== width){
			output = output + ' ' + word;
			s << output << endl;
			output.clear();

		}
		else{ // word was bigger than width
			if (len > width){
				if (!output.empty()){
				s << setw(width) << output << endl;
				}
				output.clear();
				int x = 0;
				for(int i = 0; i < len; ++i){
					output += word[i];
					x++;
					if (x == width){
						s << setw(width) << output << endl;
						x = 0;
						output.clear();
					}
				}
			}
			else{
				s << setw(width) << output << endl;
				output.clear();
				output = word;
			}
		}
	}
	cout << s.str();
}

void wordWrapCenter(int width){
	string output;
	string word;
	ostringstream s{output};

	while(true){
		cin >> word;

		int len = word.length();
		int outputLen = output.length();
		int padding = (len+width)/2;
		if (cin.eof()){
			if (!output.empty()){
				s << setw(padding)  << output<< endl;
			}
			break;
		}
		if (output.empty() && len + outputLen < width){
			s << setw(padding) << output;
			output = word;
		}
		else if (output.empty() && len + outputLen == width){
			output = word;
			s << output << endl;
			output.clear();
		}
		else if (len + outputLen + 1 < width ){
			output = output + ' ' + word;
		}
		else if (len + outputLen + 1 == width){
			output = output + ' ' + word;
			s << output << endl;
			output.clear();

		}
		else{ // word was bigger than width
			if (len > width){
				if (!output.empty()){
				s << setw(padding) << output << endl;
				}
				output.clear();
				int x = 0;
				for(int i = 0; i < len; ++i){
					output += word[i];
					x++;
					if (x == width){
						s << setw(padding) << output << endl;
						x = 0;
						output.clear();
					}
				}
			}
			else{
				s << endl << setw(padding) << word;
				output.clear();
				output = word;
			}
		}
	}
	cout << s.str();
}

int main(int argc, char* argv[]){
	if(argc != 1 && argc != 3 && argc != 4) invalid();

	string wFlag = "-w";
	string textWidthFlag;
	string dirFlag = "-l";
	int textWidth = 25;

	if (argc == 3){
		wFlag = argv[1];
		textWidthFlag = argv[2];

		istringstream iss{textWidthFlag};
		if (!(iss >> textWidth) || wFlag != "-w" || textWidth < 1){
			invalid();
		}
	}

	if (argc == 4){
		wFlag = argv[1];
		textWidthFlag = argv[2];
		dirFlag = argv[3];
		
		istringstream iss{textWidthFlag};
		if (!(iss >> textWidth) || wFlag != "-w" ||
			(dirFlag != "-l" && dirFlag != "-c" && dirFlag != "-r")) {
			invalid(); 
		}
	}
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

