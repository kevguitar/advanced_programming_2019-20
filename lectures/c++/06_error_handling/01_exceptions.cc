#include <cmath>
#include <iostream>

// implment a square root function that "deals with" negative
// numbers. Moreover according to the logic of the program, d should
// never be greater than 50
double square_root(const double d);

struct Negative_number {}; /* exception is simple struct */

struct Bigger_than_expected {};

int main() {
  try { // "try ... catch" can be inside any function
    std::cout << "please insert a number\n";
    double number;
    std::cin >> number;
    auto d = square_root(number);
    std::cout << "square root of " << number << " is " << d << '\n';
    return 0;
  } catch (const Negative_number) {
    std::cerr << "The square root of a negative number is a complex number.\n"
                 "square_root() is "
              << "limited to handle positive double numbers.\n";
    return 1;     // Exit from the main by returning 1.
  } catch (const Bigger_than_expected) {
    std::cerr << "The function square_root has been called with a parameter "
                 "greater than 50.\n"
              << "This means there is a bug in the algorithm that generated "
                 "this number.\n";
    return 2;     // Exit from the main by returning 2.
  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n";
    return 3;     // Exit from the main by returning 3.
  }
}

double square_root(const double d) {
  // test the pre-conditions (Here: d is positive and smaller than 50)
  if (d < 0)
    throw Negative_number{};   // Throw an exception, to be caught by a catch 
                               // clause.
  if (d > 50)
    throw Bigger_than_expected{};
  return std::sqrt(d);
}
