#include "polynomial.h"

// Returns the degree of the polynomial
int Polynomial::degree() const{
	return capacity - 1 == 0 ? -1 : capacity - 1;
}

//constructor no arguments
Polynomial::Polynomial(){
	capacity = 1;
	coeffs = new Rational[capacity];
}

//constructor 1 argument
Polynomial::Polynomial(int size){
	capacity = size;
	coeffs = new Rational[capacity];
}

//deconstructor 
Polynomial::~Polynomial(){
	delete[] coeffs;
}

//copy constructor
Polynomial::Polynomial(const Polynomial &other){
	capacity = other.capacity;
	coeffs = new Rational[capacity];
	for(int i = 0; i < other.capacity; i++){
		coeffs[i] = other.coeffs[i];
	}
}

//move constructor
Polynomial::Polynomial(Polynomial &&other){
	capacity = other.capacity;
	coeffs = other.coeffs;
	other.coeffs = nullptr;
}

// copy assignment operator
Polynomial &Polynomial::operator=(const Polynomial &other){
	Polynomial temp{other};
	swap(temp);
	return *this;
}

// move assignment operator
Polynomial &Polynomial::operator=(Polynomial &&other){
	swap(other);
	return *this;
}


// Swaps the fields of "this" polynomial and the other one
void Polynomial::swap(Polynomial &other){
	using std::swap;
	swap(capacity,other.capacity);
	swap(coeffs,other.coeffs);
}

// Starts at the end of coeffs[] and determines where the first 
// non-zero rational is and shrinks the coeffs.
// NOTE: [1/2,3/4,0,1/2,0,0,0] becomes [1/2,3/4,0,1/2]
void Polynomial::simplifyPoly(){
	// Does not run if the capacity is 1
	if (capacity != 1){
		int newSize = capacity;
		while(coeffs[newSize-1].isZero()){
			--newSize;
			if (newSize == 1) break;
		}

		Polynomial temp{newSize};
		for(int i = 0; i < newSize; ++i){
			temp.coeffs[i] = coeffs[i];
		}
		swap(temp);
	}
}


// Returns a new Polynomial object with "this" and rhs added.
Polynomial Polynomial::operator+(const Polynomial &rhs) const{
	// If the capacity is smaller then make a copy
	// of "this" and just add them together and return copy
	if (rhs.capacity <= capacity){
		Polynomial toReturn{*this};
		for (int i = 0; i < rhs.capacity; ++i){
			toReturn.coeffs[i] = toReturn.coeffs[i] + rhs.coeffs[i];
		}
		return toReturn;
	}
	else {
		// if Rhs has a bigger capacity, make a copy of rhs and 
		// add "this" to the copy and return copy
		Polynomial toReturn{rhs};
		for (int i = 0; i < capacity; ++ i){
			toReturn.coeffs[i] = toReturn.coeffs[i] + coeffs[i];
		}
		return toReturn;
	}
}
// Returns a new Polynomial object with "this" subtracted by rhs.
Polynomial Polynomial::operator-(const Polynomial &rhs) const{
	// if rhs is smaller then "this", copies over the rationals
	//  that were subtracted and any remaining rationals that were
	//  not subtracted over to the copy.
	if (rhs.capacity <= capacity){
		Polynomial toReturn{capacity};
		for (int i = 0; i < rhs.capacity; ++i){
			toReturn.coeffs[i] = coeffs[i] - rhs.coeffs[i];
		}
		for (int i = rhs.capacity; i < capacity; ++i){
			toReturn.coeffs[i] = coeffs[i];
		}
		return toReturn;
	}
	// if rhs was bigger than this, copies over the rationals from
	//   this subtracted by rhs into the copies.coeffs. Then negates
	//   all the remaining rationals from rhs to the copy.
	else {
		Polynomial toReturn{rhs.capacity};
		for (int i = 0; i < capacity; ++ i){
			toReturn.coeffs[i] =  coeffs[i] - rhs.coeffs[i];
		}
		for (int i = capacity; i < rhs.capacity; ++i){
			toReturn.coeffs[i] = -rhs.coeffs[i];
		}
		return toReturn;
	}
}

// Runs two forloops on the coeffs[] and rhs.coeffs[] to 
//	multiply the new produce into a new polynomial and returns
Polynomial Polynomial::operator*(const Polynomial &rhs) const{
	int degreeSize = capacity + rhs.capacity -1;
	Polynomial toReturn{degreeSize};
	for(int i = 0; i < capacity; ++i){
		if (!coeffs[i].isZero()){
			for(int j = 0; j < rhs.capacity; ++j){
				if(!rhs.coeffs[j].isZero()){
					toReturn.coeffs[i+j] = 
						toReturn.coeffs[i+j] + 
						coeffs[i]*rhs.coeffs[j];
				}
			}
		}
	}
	return toReturn;
}

// Function mimics long division.
Polynomial Polynomial::operator/(const Polynomial &rhs) const{
	// If the result of the division is less then the predicted 
	//  quotient size then that means the division will produce no
	//  quotient and just return the Zero Polynomial.
	int capacitySize = capacity - rhs.capacity + 1;
	if (capacitySize <= 0){
		return {};
	}

	// Creates toReturn and tempThis
	// tempThis a copy of "this" and will be mutated
	//  directly to return the next rational coefficient to
	//  insert in the tempThis.coeffs
	Polynomial toReturn{capacitySize};
	Polynomial tempThis{*this};
	
	for(int i = capacity-1; i >= rhs.capacity-1; --i){
		//ans is the calculated coefficient
		Rational ans = tempThis.coeffs[i]/rhs.coeffs[rhs.capacity-1];
		//place the ans to our toReturn (quotient) array
		toReturn.coeffs[i-rhs.capacity+1] = ans;
		// create a temporary array that is the ans polynomial
		Polynomial tmp{i-rhs.capacity+2};
		tmp.coeffs[tmp.capacity-1] = ans;
		// take that ans polynomial and multiply it with the rhs polynomial
		Polynomial tmp2 = rhs*tmp;
		// take the product of ans polynomial and rhs polynomial and subtract it
		// to the to tempThis (which is the remainder)
		Polynomial check = tempThis - tmp2;
		tempThis = check;
	}
	
	return toReturn;
}

// Similar behaviour to operator/ 
Polynomial Polynomial::operator%(const Polynomial &rhs) const{
	// If the result of the division is less then the predicted
	//  quotient size then that means the division will be the 
	//  as "this". Thus, creates a copy of this and returns it.
	int capacitySize = capacity - rhs.capacity + 1;
	if (capacitySize <= 0){
		Polynomial same = *this;
		return same;
	}
	//  Behaviour is similar to operator/ except tempThis is called
	//  remainder. Remainder is returned instead.
	Polynomial quotient{capacitySize};
	Polynomial remainder{*this};

	for(int i = capacity-1; i >= rhs.capacity-1; --i){
		Rational ans = remainder.coeffs[i]/rhs.coeffs[rhs.capacity-1];
		quotient.coeffs[i-rhs.capacity+1] = ans;
		Polynomial tmp{i-rhs.capacity+2};
		tmp.coeffs[tmp.capacity-1] = ans;
		Polynomial tmp2 = rhs*tmp;
		Polynomial check = remainder - tmp2;
		remainder = check;
	}

	return remainder;
}

// Output operator for polynomials 
// Outputs the polynomial formatted ex: (3/2)x^3 + (1/1)x + (1)
std::ostream& operator<<(std::ostream& out, const Polynomial &poly){
	// creates a copy of poly and simplifies it to get rid of 
	//  beginning zero rationals.
	Polynomial copyPoly{poly};
	copyPoly.simplifyPoly();
	// Beginning case
	if (copyPoly.capacity == 1){
		if (!copyPoly.coeffs[0].isZero()){
			out << '(' << copyPoly.coeffs[0] << ')';
		}
		else{
			out << copyPoly.coeffs[0];
		}
	}
	// Case where there are 2 terms
    else if (copyPoly.capacity == 2){
		if (!copyPoly.coeffs[1].isZero()){
			out << '(' << copyPoly.coeffs[1] << ")x";
		}
	}
	// Case where there are more than 2 terms
	else{
		out << '(' << copyPoly.coeffs[copyPoly.capacity-1] << ")x^"
			<< copyPoly.capacity-1;
	}
	// go through the rest of the copied coeffs array
	for(int i = copyPoly.capacity-2; i >= 0; --i){
		if (!copyPoly.coeffs[i].isZero()){
			out << " + ";
			if (i == 0){
				out << '(' << copyPoly.coeffs[i] << ')';
			}
			else if (i == 1){
				out << '(' << copyPoly.coeffs[i] << ")x";
			}
			else{
				out << '(' << copyPoly.coeffs[i] << ")x^" << i;
			}
		}
	}
	return out;
}

// Input operator for Polynomials
std::istream &operator>>(std::istream &in, Polynomial &poly){
	// Reads a line, then rational objects then ints until end of line.
	// Simplifies the polynomial at the end before returning in.
	Rational r;
	int exp;
	std::string s;
	std::getline(in,s);
	std::istringstream iss(s);

	iss >> r;
	iss >> exp;
	// NOTE: Deletes the poly.coeffs[] just incase.
	delete[] poly.coeffs;
	poly.capacity = exp+1;
	poly.coeffs = new Rational[poly.capacity];
	poly.coeffs[poly.capacity-1] = r;

	while(iss >> r){
		iss >> exp;
		poly.coeffs[exp] = r;
	}

	poly.simplifyPoly();
	return in;
}

