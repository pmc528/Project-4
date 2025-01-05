// Author: Ryan Sedlacek and Peter Chang
// using google c++ style guide: https://google.github.io/styleguide/cppguide.html#Header_Files

#include "polynomial.h"

// Override for << operator
ostream& operator<<( ostream &output, const Polynomial& p ) {
  if (p.size == 0) // if empty just print as 0
    return (output << 0);
  
  Term *current = p.head->next;
  do{
    if(current->coeff != 0) { // Print terms with non zero coefficients
      
      // Add term sign (positive/negative) to output
      if (current == p.head->next) // First term has different rules for signage
        output << ((current->coeff < 0) ? "-" : "");
      else
        output << ((current->coeff < 0) ? " - " : " + ");

      // Add coefficient to output, coefficients of 1 or -1 are not printed unless power = 0
      if (abs(current->coeff) != 1 || current->power == 0)
        output << abs(current->coeff);

      // Add x^, x or nothing to output depending if power > 1, = 1 or 0
      if (current->power != 0)
        (abs(current->power) == 1) ? output << "x" : output << "x^" << current->power;
    }
    current=current->next;
  } while(current != p.head); // Stop when loops around back to head.

  return output;
}

// Default constructor, creates dummy header
Polynomial::Polynomial() {
  this->size = 0; //default of size is set to 0
  this->head = new Term(); //Create dummy header
  this->head->power = 0; // needed for coefficient( int power ) to work
  this->head->next = nullptr; //Set next to nullptr
  this->head->prev = nullptr;
}

// Copy constructor
Polynomial::Polynomial( const Polynomial& p ){
  // Construct the polynomial like a default one
  this->size = 0;
  this->head = new Term();
  this->head->power = 0;
  this->head->next = nullptr;
  this->head->prev = nullptr;

   // Then iterate through p's terms and add them to this
  if (p.size != 0) {
    Term *current = p.head->next;
    do {
      changeCoefficient(current->coeff, current->power);
      current=current->next;
    } while(current != p.head); // Stop when loops around back to head.
  }
}

// Destructor
// Remove all terms and then delete head.
Polynomial::~Polynomial() {
  if (head->next != nullptr) { // no terms to remove if empty
    Term *current = head->next;
    Term *currentTemp;
    while (current != head) {
      currentTemp = current;
      current = current->next;
      remove(currentTemp);
    }
  }
  delete(head);
  head = nullptr;
}

//Main public functions!
// degree() returns degree of polynomial by returning highest power
// An empty polynomial will return 0
int Polynomial::degree( ) const {
  if(head->next == nullptr){ // An empty polynomial will return 0
    return 0;
  }
  return head->next->power; // First term is highest since this linked list is sorted by power
}

// coefficient(int power) takes a intertger and if a term of that power exists returns the
// coefficient C where a term is Cx^power. If such a term does not exists returns 0.
double Polynomial::coefficient( const int power ) const {
  if (head->next == nullptr) // Return 0 if polynomial empty
    return 0;

  // Iterate through terms to find term of power
  Term *current=head->next;
  while (current->power != power && current != head)
    current = current->next;
  return current->coeff;
}

// changeCoefficient( double newCoefficient, int power) sets term of power to have coefficient if
// it exists in the polynomial. If it doesn't it will add a term of power with coefficient.
// TODO: What should the return bool be used for?
bool Polynomial::changeCoefficient( const double newCoefficient, const int power ){
  if(head->next == nullptr){ // If no terms, add one and return
    insert(head, newCoefficient, power); // we insert BEFORE head which on an empty polynomial is also the
    // first term. Crazy, I know.
    return true;
  }

  // Add term before any term lower than it
  Term *current = head->next;
  while (current->power > power && current != head) // First get term of = or smaller power
    current = current->next;
  if (current == head) {// if current is head, this means it looped around, add term to end
    insert(head, newCoefficient, power);
    return true;
  }
  if (current->power == power) // if the new coefficient is 0 it will remove the term istead of modifying it,
  // we don't allow terms of coefficient 0 in polynomial
    (newCoefficient == 0) ? remove(current) : current->coeff = newCoefficient;
  else // this else means power > current->power
    insert(current, newCoefficient, power);
  return true;
}

// Arithmetic operator overrides!
// operator+ will combine like terms and insert unlike terms, uses operator+=, scroll down to read that
Polynomial Polynomial::operator+( const Polynomial& p ) const { return (Polynomial(*this) += p); } // 1 line! 
// that's the payoff!

//operator- will combine like terms and insert unlike terms except through subtraction instead of add, uses operator-=
Polynomial Polynomial::operator-( const Polynomial& p ) const { return (Polynomial(*this) -= p); } // also 1 line!

// Boolean comparison operator overrides!
// operator== returns true if p1 and p2 have identical terms, otherwise false.
bool Polynomial::operator==( const Polynomial& p) const {
  // Polynomials of unequal size are not equal
  if(size != p.size)
    return false;

  // handle case where size == p.size == 0
  if(size == p.size && size == 0)
    return true;
  
  //iterate through and confirm that terms are equal.
  Term *p2Current = head->next;
  Term *p1Current = p.head->next;
  while (p1Current != head) {
    if (p1Current->power != p2Current->power || p1Current->coeff != p2Current->coeff)
      return false;
    p2Current = p2Current->next;
    p1Current = p1Current->next;
  }
  return true;
}

// operator!= returns true if the terms don't match
// Very simple implementation, return the reverse of operator==
bool Polynomial::operator!=( const Polynomial& p ) const { return !(*this==p); }

// Assignment operator overrides!
//operator= will empty out terms and add all of the ones from p.
Polynomial& Polynomial::operator=( const Polynomial& p ) {
  // Handle self-assignment
  if (*this == p)
    return *this;

  // First remove all terms in the current list
  Term *current;
  if (size != 0) {
    current = head->next;
    Term *currentTemp; // Need temp variable to prevent nullptr issues
    while (current != head) { // Iterate and remove
      currentTemp = current;
      current = current->next;
      remove(currentTemp);
    }
  }

  // Now add p terms verbatim to this
  if (p.size != 0) {
    current = p.head->next;
    while (current != p.head) {
      insert(head, current->coeff, current->power); //inserting on head will put them in order
      current = current->next;
    }
  }
  return *this;
}

// operator+= will combine polynomials by adding like terms and inserting unlike terms
Polynomial& Polynomial::operator+=( const Polynomial& p ) {
  if (p.size == 0) { // nothing to add from an empty list
    return *this;
  }
  // We could do this using changeCoefficient and coefficient but that would lead to a
  // high time complexity due to how those functions always iterate from the head. A faster 
  // approach is iterate through p2 terms and insert/combine p2 terms into p1 appropriately.
  Term *p2Current = p.head->next; // p2 is p
  Term *p1Current; // p1 is this
  if (head->next == nullptr) // if p1 is empty then start at the head, it will cause all terms to be added
    p1Current = head;
  else
    p1Current = head->next;
  bool removeBool = false; // This and the below lines are used handling the p1 coeff = -p2 coeff case
  Term *p1CurrentTemp;
  while(p2Current != p.head) {
    if (p2Current->power == p1Current->power && p1Current != head) { // Combine equal power terms
      p1Current->coeff += p2Current->coeff; // No need to use changeCoefficient when we have the term...
      if (p1Current->coeff == 0) { // save p1Current and mark for removal if p1 coeff + p2 coeff = 0
        removeBool = true;
        p1CurrentTemp = p1Current;
      }
      p2Current = p2Current->next;
      p1Current = p1Current->next; 
      if (removeBool) { // remove coeff 0 term from p1
        remove(p1CurrentTemp);
        removeBool = false;
      }
    } else if (p2Current->power > p1Current->power || p1Current == head) { // Insert if p1 power is lower than p2s
    // or if p1Current is at head (which means it looped through all terms)
      insert(p1Current, p2Current->coeff, p2Current->power);
      p2Current = p2Current->next;
    } else { // p1 power is greater than p2 power, iterate p1Current (note: if p1 == head it hits condition above)
      p1Current = p1Current->next;
    }
  }
  return *this;
}

// operator-= will combine polynomials by subtracting like terms and inserting unlike terms
Polynomial& Polynomial::operator-=( const Polynomial& p ) {
  // I *knoooow* how much we hate code duplication but neither +=operater or changeCoefficient lend
  // themselves to reuse without adding a keyword arguement.
  // NOTE: I removed the comments, the logic is nearly identical to +=, read those comments
  if (p.head->next == nullptr)
    return *this;
  
  Term *p2Current = p.head->next;
  Term *p1Current;
  if (head->next == nullptr)
    p1Current = head;
  else
    p1Current = head->next;
  bool removeBool = false;
  Term *p1CurrentTemp;
  while(p2Current != p.head) {
    if (p2Current->power == p1Current->power && p1Current != head) {
      p1Current->coeff -= p2Current->coeff; // Oooo its -= this time!
      if (p1Current->coeff == 0) {
        removeBool = true;
        p1CurrentTemp = p1Current;
      }
      p2Current = p2Current->next;
      p1Current = p1Current->next; 
      if (removeBool) {
        remove(p1CurrentTemp);
        removeBool = false;
      }
    } else if (p2Current->power > p1Current->power || p1Current == head) {
      insert(p1Current, -1.0*(p2Current->coeff), p2Current->power); // invert coeff sign cuz subtraction
      p2Current = p2Current->next;
    } else {
      p1Current = p1Current->next;
    }
  }
  return *this;
}

// Private methods!
//insert is used to insert a new term BEHIND the Term pos. It increases size and manages node pointers
bool Polynomial::insert( Term* pos, const double newCoefficient, const int power ){
  if (newCoefficient == 0) // zero is never a valid coeff for a term
    return false;
  //First construct new term
  Term *newTerm = new Term();
  newTerm->coeff = newCoefficient;
  newTerm->power = power;

  // Insert term into list
  if (size == 0) { // Empty list case
    newTerm->next = head;
    newTerm->prev = head;
    head->next = newTerm;
    head->prev = newTerm;
  } else { // Since this is a private method we assume term pos is a valid target, part of a correct polynomial
    newTerm->next = pos;
    newTerm->prev = pos->prev;
    pos->prev->next = newTerm;
    pos->prev = newTerm;
  }
  size++;
  return true;
}

//remove is used to remove terms and to delete them
bool Polynomial::remove( Term* pos ) {
  // Cannot remove dummy head
  if (pos==head)
    return false;
  // Since this is a private method we assume term pos is part of this
  if (size == 1) { // for single term polynomials we want to remove pointer from head so it is obvious it
  // is empty
    head->next = nullptr;
    head->prev = nullptr;
  } else { // if size is > 1. We assume that negative and 0 signs aren't possible (the only term in a 0
  //size polynomial is head)
  pos->next->prev = pos->prev;
  pos->prev->next = pos->next;
  }
  delete(pos);
  size--;
  return true;
}