#include <iostream>
using namespace std;
struct BinaryNum {
  int size; // number of elements the array currently holds
  int capacity; // number of elements the array could hold, given current
                // memory allocation to contents
  bool *contents; // heap allocated bool array
};

// This program will NOT compile until
// you fix the TODOs

// helper function for binaryToDecimal
static int pow(int b, int e){
    if (e == 0) return 1;;
    return b*(pow(b,e-1));
}

//helper function for resizing the bool Arrays.
static bool* myBoolRealloc(bool *oldArray,int size){
    /* makes a new bool array with the new doubled size
    and then copies all the old contents to the new array*/
    bool *newArray = new bool[size*2];

    for(int i = 0; i < size; ++i){
        newArray[i] = oldArray[i];
    }
    delete[] oldArray;
    return newArray;
}

BinaryNum readBinaryNum() {
    //read until not 1 or 0 with doubling strategy
    BinaryNum newBinNum;
    newBinNum.size = 0;
    newBinNum.capacity = 0;
    newBinNum.contents = nullptr;

    char c;
    while(true){
        //reads character per character on user input
        cin.get(c);
        if (c == ' ' || c == '\n' || c == 9){
            continue;
        }
        if (c != '0' && c != '1'){
            break;
        }
        // if there is no more room to store the chars
        // checks to see if this is the first time creating the heap array
        if (newBinNum.size == newBinNum.capacity){
            if (newBinNum.capacity == 0){
                newBinNum.capacity = 4;
                newBinNum.contents = new bool[newBinNum.capacity];
            } else{
                // dynamically doubles the array size if out of space
                newBinNum.contents
                    = myBoolRealloc(newBinNum.contents,newBinNum.capacity);
                newBinNum.capacity *= 2;
            }
        }

        if (c == '0'){
            newBinNum.contents[newBinNum.size] = 0;
        } else{
            newBinNum.contents[newBinNum.size] = 1;
        }

        ++newBinNum.size;
    }
    return newBinNum;
}

void binaryConcat(BinaryNum &binNum) {
   // same functionality as readBinaryNum except it appends to the end
    char c;
    while(true){
        cin.get(c);
        if (c == ' ' || c == '\n' || c == 9){
            continue;
        }        
        if (c != '0' && c != '1'){
            break;
        }
        // if there is no more room to store the chars
        if (binNum.size == binNum.capacity){
            binNum.contents 
                = myBoolRealloc(binNum.contents,binNum.capacity);
            binNum.capacity *= 2;
        }
        if (c == '0'){
            binNum.contents[binNum.size] = 0;
        } else{
            binNum.contents[binNum.size] = 1;
        }
        ++binNum.size;
    }
}

int binaryToDecimal(const BinaryNum &binNum){
    /* Loops over the array and computes 2^(binNum.size - (i+1))
    where i is the index in the array from 0 to binNum.size. */
    int value = 0;
    for(int i = 0; i < binNum.size; ++i){
        if (binNum.contents[i] == 1){
            value += pow(2, (binNum.size - (i+1)));
        }
    }
    return value;
}

void printBinaryNum(const BinaryNum &binNum, char sep){
    // First prints index 0 in the bool array then followed by
    //  the seperators and indexes.
    cout << binNum.contents[0];
    for(int i = 1; i < binNum.size; ++i){
        cout << sep << binNum.contents[i];
    }
}

BinaryNum &operator<<(BinaryNum & binNum, int num){
    // Similar to readBinaryNum, except it does not take user input
    // but rather appends 0's to the array num times.
    for(int i = 0; i < num; ++i){
        if(binNum.size == binNum.capacity){
            binNum.contents 
                = myBoolRealloc(binNum.contents,binNum.capacity);
            binNum.capacity *= 2;
        }
        binNum.contents[binNum.size] = 0;
        ++binNum.size;
    }
    return binNum;
}


// TEST HARNESS
// DO NOT MODIFY THIS FUNCTION IN ANY WAY
// Be sure to understand what the following does
// in order to create appropriate test cases.
int main() {
    const int arr_size = 4;
    BinaryNum a[arr_size];
    for (int i = 0; i < arr_size; ++i) a[i].contents = nullptr;

    bool done = false;
    while (!done) {
        char c;
        char which;
        cin >> c; // reads r, +, d, p, s or q
        if (cin.eof()) break;
        switch(c) {
            case 'r':
                cin >> which; // reads a b c or d
                delete[] a[which-'a'].contents;
                a[which-'a'].contents = nullptr;
                a[which-'a'] = readBinaryNum();
                break;
            case '+':
                cin >> which; // reads a b c or d
                binaryConcat(a[which-'a']);
                break;
            case 'p':
                cin >> which; // reads a b c or d
                char sep;
                cin >> sep; // reads one char for sep char.
                printBinaryNum(a[which-'a'],sep);
                cout << endl;
                break;
            case 'd':
                cin >> which; // reads a b c or d
                cout << binaryToDecimal(a[which-'a']) << endl;
                break;
            case 's':
                cin >> which; // reads a b c or d
                int x;
                cin >> x; // reads how much to shift by.
                a[which-'a'] << x;
                break;
            case 'q':
                done = true;
                break;
        }
    }
    for (int i = 0; i < arr_size; ++i) delete[] a[i].contents;
};

