#include "rational.h"

int gcd(int x,int y){
	if (y == 0) return x;
	return gcd(y, x % y);
}

// Simplifies by calculating gcd and then dividing the fields
void Rational::simplify(){
	int n = gcd(num,den);
	num = num/n;
	den = den/n;
	if(den < 0){
		den = -den;
		num = -num;
	}
}

//Rational Class Constructor
Rational::Rational(int num, int den){
	//moves the negative the numerator
	this->num = num;
	this->den = den;
	if (this->den < 0){
		this->den = -den;
		this->num = -num;
	}
}
// All operators calculate Nums and Dens then simplfies
Rational Rational::operator+(const Rational &rhs) const{
	int resultNum = num*rhs.den + den*rhs.num; 
	int resultDen = den*rhs.den;
	Rational result{resultNum, resultDen};
	result.simplify();
	return result;
}

Rational Rational::operator-(const Rational &rhs) const{
	int resultNum = num*rhs.den - den*rhs.num; 
	int resultDen = den*rhs.den;
	Rational result{resultNum, resultDen};
	result.simplify();
	return result;
}

Rational Rational::operator*(const Rational &rhs) const{
	int resultNum = num*rhs.num;
	int resultDen = den*rhs.den;
	Rational result{resultNum,resultDen};
	result.simplify();
	return result;
}

Rational Rational::operator/(const Rational &rhs) const{
	int resultNum = num*rhs.den;
	int resultDen = den*rhs.num;
	Rational result{resultNum,resultDen};
	result.simplify();
	return result;
}

Rational &Rational::operator+=(const Rational &rhs){
	int resultNum = num*rhs.den + den*rhs.num; 
	int resultDen = den*rhs.den;
	num = resultNum;
	den = resultDen;
	(*this).simplify();
	return *this;
}

Rational &Rational::operator-=(const Rational &rhs){
	int resultNum = num*rhs.den - den*rhs.num; 
	int resultDen = den*rhs.den;
	num = resultNum;
	den = resultDen;
	(*this).simplify();
	return *this;
}

Rational Rational::operator-() const{
	Rational negated{-num,den};
	return negated;
}

int Rational::getNumerator() const{
	return num;
}

int Rational::getDenominator() const{
	return den;
}

bool Rational::isZero() const{
	return !num;
}

// prints out no denominator if den = 1.
std::ostream &operator<<(std::ostream &out, const Rational &rat){
	rat.den == 1 ? out << rat.num : out << rat.num << '/' << rat.den;
	return out;
}

// reads in input and then simplifies if possible. Fixes
// the negative sign afterwards
std::istream &operator>>(std::istream &in, Rational &rat){
	char l;
	in >> rat.num;
	in >> l;
	in >> rat.den;
	rat.simplify();
	return in;
}







