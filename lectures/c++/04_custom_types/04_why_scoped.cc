#include <iostream>

enum month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

<<<<<<< HEAD

// Take-home messages:
// 1) Never use "using namespace" in header files! Only use them in source files
// 2) If you need to use 
using namespace std;

// using std::cout;    // If only this shall be used from std
// using std::endl;

int main() {
  cout << nov << endl;
  // cout << dec << endl; // error
=======
using namespace std;

int main() {
  cout << nov << endl;
  // cout << dec << endl;
>>>>>>> 9282c88989c7df919152ca3ebcc786da20164736

  return 0;
}
