#include <iostream>

enum color { red, yellow, green };
// enum color{red=0, yellow=1, green=2}; // equivalent

// constexpr cm_to_inch: use (in C) to e.g. convert units
// in C++ not advisable since constexpr is evaluated at runtime 


void dwim(const color c) {
  switch (c) {
    case red:
      std::cout << "option 1: red\n";
      break;          // "break" is required, otherwise all cases will be 
                      // executed one after another
    case yellow:
      std::cout << "option 2: yellow\n";
      break;
    case green:
      std::cout << "option 3: green\n";
      break;
    default:
      std::cout << "unknown option\n";  // should I exit the program?
      break;
  }
}

int main() {
  color opt{red};
  // opt = 3; // cannot assign int to enum
  int a{opt};  // but they implicitly converts to integers

  dwim(opt);

  dwim(yellow);

  // dwim(2); // error
  dwim(color(2));  // works but why you may want to write this?

  dwim(color(6));  // ???

  return 0;
}
