// A Polynomial class                                  
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <string>
using namespace std;

 struct Term {     // a term on the sparse polynomial
    double coeff;   // the coefficient of each term
    int power;      // the degree of each term
    Term *prev;     // a pointer to the previous higher term
    Term *next;     // a pointer to the next lower term
  };


// ASSUMPTIONS: The function of must mehtods here are straight foward and by
// google standards don't justify long commentary. One main implementation 
// characteristic is that an empty polynomial has a dummy header that does 
// has nullptr next and prev. This implementation requires checking for nullptrs
// but prevents some bugs where the dummy header is intpreted as a term.
// Performance was prefered over reducing code duplication, this means mehtods
// like changeCoefficient aren't widely utilized because they always search from
// head in our implementation. It was tempting to use keyword arugements to have
// methods be more reusable, the issue is that generality also adds oppertunity
// for misuse and complexity. The insert and remove methods are private and 
// assume valid imputs are being given. Verifying that a passed in term is in
// the linked list would require iterating the list each time.
class Polynomial {
  // Overloaded <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
  // Empty polynomials print as 0
  friend ostream& operator<<( ostream &output, const Polynomial& p );
  // Constructor: the default is a 0-degree polynomial with 0.0 coefficient
 public:
  // Member functions
  Polynomial( );
  Polynomial( const Polynomial& p );
  ~Polynomial( );
  int degree( ) const; // returns the degree of a polynomial
  double coefficient( const int power ) const; 
                 // returns the coefficient of the x^power term.
  bool changeCoefficient( const double newCoefficient, const int power );
                 // replaces the coefficient of the x^power term

  // Arithmetic operators
  Polynomial operator+( const Polynomial& p ) const;
  Polynomial operator-( const Polynomial& p ) const;

  // Boolean comparison operators
  bool operator==( const Polynomial& p ) const;
  bool operator!=( const Polynomial& p ) const;

  // Assignment operators
  Polynomial& operator=( const Polynomial& p );
  Polynomial& operator+=( const Polynomial& p );
  Polynomial& operator-=( const Polynomial& p );
 private:
 
  int size;         // # terms in the sparse polynomial
  Term *head;       // a pointer to the doubly-linked circular list of
                    // sparse polynomial

  // inserts a term of power and coeff BEFORE pos
  bool insert( Term* pos, const double newCoefficient, const int power );
  // removes term pos and deletes it
  bool remove( Term* pos );

};

#endif
