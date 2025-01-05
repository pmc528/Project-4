#include <iostream>
#include "polynomial.h"
#include <string>
using namespace std;

int main( )

{

  Polynomial p1;

  p1.changeCoefficient( 1, 1 );

  p1.changeCoefficient( 4, 4 );

  p1.changeCoefficient( 2.2, 2 );

  p1.changeCoefficient( -3.8, 3 );

  cout << "p1 = " << p1 << endl;

  p1.changeCoefficient( 0, 2 );

  cout << "p1 = " << p1 << endl;

  Polynomial p2 = p1;

  p2.changeCoefficient( 9.5, 2 );

  cout << "p1 = " << p1 << endl;

  cout << "p2 = " << p2 << endl;

  Polynomial p3 = p1 + p2;

  cout << "p3 = " << p3 << endl;

  //________________________________________//
  cout << endl << "Beginning testing for each function..." << endl;

  //Create some test plynomials to run through the functions
  Polynomial test1;

  test1.changeCoefficient(6,9);
  test1.changeCoefficient(7,7);
  test1.changeCoefficient(4,4);
  test1.changeCoefficient(-3.8,3);

  Polynomial test2;

  test2.changeCoefficient(2.5,4);
  test2.changeCoefficient(3.8,3);
  test2.changeCoefficient(1,1);
  test2.changeCoefficient(100,0);

  Polynomial test3; //empty polynomial

  Polynomial test4;

  test4.changeCoefficient(-2.5,4);
  test4.changeCoefficient(4.5,3);
  test4.changeCoefficient(6,2);
  test4.changeCoefficient(-1,1);
  test4.changeCoefficient(100,0);
  test4.changeCoefficient(0,0);

  Polynomial test5;

  test5.changeCoefficient(3,0);

  Polynomial test6; //empty polynomial
  

  //print out the test polynomials
  cout << "test1 plynomial: " << test1 << endl;
  cout << "test2 plynomial: " << test2 << endl;
  cout << "test3 plynomial: " << test3 << endl;
  cout << "test4 plynomial: " << test4 << endl;
  cout << "test5 plynomial: " << test5 << endl;
  cout << "test6 plynomial: " << test6 << endl;

  //test degree funtion
  cout << "Degree of test1 polynomial: " << test1.degree() << endl;
  cout << "Degree of test2 polynomial: " << test2.degree() << endl;
  cout << "Degree of empty test3 polynomial: " << test3.degree() << endl;
  cout << "Degree of test5 polynomial with only coefficient: " << test3.degree() << endl;
  //test coefficient function
  cout << "Coefficient of test1: " << test1.coefficient(9) << endl;
  cout << "Coefficient of test2: " << test2.coefficient(3) << endl;  
  cout << "Coefficient of test5: " << test5.coefficient(0) << endl;  
  cout << "Coefficient of empty polynomial test3: " << test3.coefficient(0) << endl;  
  //test changeCoefficient function
  test1.changeCoefficient(8, 9);
  cout << "Change first coefficient of test1 to 8 for expo of 9: " << test1 << endl;
  test2.changeCoefficient(2.6, 4);
  cout << "Change first coefficient of test2 to 2.6 for expo of 4: " << test2 << endl;
  test2.changeCoefficient(0, 4);
  cout << "Change first coefficient of test2 to zero for expo of 4: " << test2 << endl;
  //test arithmetic operators
  cout << "test1 + test2: " << test1 + test2 << endl;
  cout << "test1 + test3: " << test1 + test3 << endl;
  cout << "test1 - test2: " << test1 - test2 << endl;
  cout << "test2 - test1: " << test2 - test1 << endl;
  cout << "test1 - test3: " << test1 - test3 << endl;
  cout << "test2 - test5: " << test2 - test5 << endl;
  cout << "test5 - test3: " << test5 - test3 << endl;
  //test assignment operators
  test1 += test2;
  cout << "test1 += test2: " << test1 << endl;
  test1 -= test2;
  cout << "test1 -= test2: " << test1 << endl;
  test3 -= test4;
  cout << "test3 -= test4: " << test3 << endl;
  test3 += test4;
  cout << "test3 += test4: " << test3 << endl;
  test4 += test3;
  cout << "test4 += test3: " << test4 << endl;
  test4 -= test3;
  cout << "test4 -= test3: " << test4 << endl;
  Polynomial assign_test = test1 = test1;
  cout << "Set test1 = test1: " << assign_test << endl;
  Polynomial assign_test2 = test3 = test4;
  cout << "Set empty polynomial test3 equal to test4: " << assign_test2 << endl;
  Polynomial assign_test3 = test4 = test6;
  cout << "Set test4 equal to empty polynomial test6: " << assign_test3 << endl;
  //test copy constructor
  Polynomial test7 = test1;
  cout << "Copy constructor to create new polynomial test7 from test1: " << test7 << endl;
  //test copy constructor on empty polynomial
  Polynomial test8 = test3;
   cout << "Copy constructor to create new polynomial test8 from an empty polynomial: " << test8 << endl;
  //test = operator
  test7 = test2;
  cout << "= operator to set test7 equal to test2: " << test7 << endl;
  //test boolean operators
  bool bool_test1 = test3 == test6;
  cout << "Is test3 equal to test6? " << bool_test1 << endl;
  bool bool_test2 = test3 != test6;
  cout << "Is test3 not equal to test6? " << bool_test2 << endl;
  bool bool_test3 = test2 == test2;
  cout << "Does test2 equal test2? " << bool_test3 << endl;
  bool bool_test4 = test3 == test1;
  cout << "Does test3 equal test1? " << bool_test4 << endl;
}
