#include <iostream>

struct X {
  int a = 5;  // in-class initialization
  double b;   // with {}, b would be initialized to 0. Without {}, random double.
  char c = 'a';
  X() = default;  // in-class initializers are used by the constructors:
                  /* (This is not needed, but it increases readability!)
                     This obliges the complier to generate the default 
                     constructor, even if there is a custom compiler. */
};

/* Built-in types (int, double, char*, ...) are automatically initialized to a 
   value (random value or zero), while custom types (e.g. std::string) are never 
   automatically initialized, i.e. null pointer. */

struct Y {
  int a = 77;
  double b;
  char c = 'a';
  Y() : a{5} {}  // what it is written here wins the in-class initialization
  Y(const Y&) = delete;
};

int main() {
  X x1;    // compiler-generated default ctor
  X x2{};  // compiler-generated default ctor calls {} on uninitialized vars
  std::cout << x1.a << "--" << x1.b << "--" << x1.c << "\n";
  std::cout << x2.a << "--" << x2.b << "--" << x2.c << "\n\n";

  Y y1;    // default ctor
  Y y2{};  // default ctor
  std::cout << y1.a << "--" << y1.b << "--" << y1.c << "\n";
  std::cout << y2.a << "--" << y2.b << "--" << y2.c << "\n";

  // Y y3{y2}; // error: call to a deleted function

  return 0;
}
