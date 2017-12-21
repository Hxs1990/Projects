#ifndef POLY_H
#define POLY_H
#include <iostream>
#include <utility>
#include "rational.h"
#include <sstream>
struct Polynomial {
    Rational *coeffs; // heap allocated array
    int capacity;     // size of allocated array

    Polynomial();     //creates the 0 polynomial
    Polynomial(int size); //creates the size-1 degree 0 polynomial

    //Swapping two Polynomials
    void swap(Polynomial &other);

    //Big five
    ~Polynomial();
    Polynomial(const Polynomial &other);
    Polynomial(Polynomial &&other);
    Polynomial &operator=(const Polynomial &other);
    Polynomial &operator=(Polynomial &&other);

    // Arithmetic operations behave in the standard way 
    Polynomial operator+(const Polynomial &rhs) const;
    Polynomial operator-(const Polynomial &rhs) const;
    Polynomial operator*(const Polynomial &rhs) const;

    //returns quotient after long division
    Polynomial operator/(const Polynomial &rhs) const; 

    //returns remainder after long division
    Polynomial operator%(const Polynomial &rhs) const; 

    // degree of the zero polynomial is -1
    int degree() const;

    //simplifies a polynomial by getting rid of trailing zeros
	//from the end of the array to the beginning
    void simplifyPoly();
};

// Print with decresing exponents.
std::ostream& operator<<(std::ostream& out, const Polynomial &poly);

// Read until newline consisting of one polynomial in specified format
std::istream& operator>>(std::istream& in, Polynomial &poly);
#endif


