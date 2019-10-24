#include <iostream>

enum month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

// Take-home messages:
// 1) Never use "using namespace" in header files! Only use them in source files
// 2) If you need to use 
using namespace std;

// using std::cout;    // If only this shall be used from std
// using std::endl;

int main() {
  cout << nov << endl;
  // cout << dec << endl; // error

  return 0;
}
