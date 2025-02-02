#include <assert.h>
#include <cmath>
#include <iostream>

#include "ap_error.h"

/* 
Compile with:
c++ 04_assert.cc -o 04_assert.x -Wall -Wextra -g -std=c++11 (-DNDEBUG)
*/

// implment a square root function that "deals with" negative
// numbers. Moreover according to the logic of the program, d should
// never be greater than 50
double square_root(const double d);

int main() {
  try {
    std::cout << "please insert a number\n";
    double number;
    std::cin >> number;
    double d = square_root(number);
    std::cout << "square root of " << number << " is " << d << '\n';
    return 0;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n";
    return 3;
  }
}

double square_root(const double d) {
  // test the pre-conditions
  assert(d >= 0 && d <= 50);  // provided by C, no exceptions

  /* asset is a compile flag that tells the compiler to skip checks if -DNDEBUG
     is called */

  /* error vs assets: when reading external input, use errors.
     when reading internal code, use assets to be able to speed up the code. */
  
  /* Don't comment out debugging code, or use custom flags. Assets are much more
     simple. */


  // AP_ASSERT(d>=0 && d<=50) <<  "d should be in the range [0,50]";

  // AP_ASSERT_IN_RANGE(d,0,50);
  return sqrt(d);
}
