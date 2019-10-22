#include <iostream>
#include <string>

struct Foo {
  int _i;       /* Variable members of the class are named (conventionally) 
                   with underscore prefix. Variables here have already been 
                   constructed. In this area, you cannot use "=". Instead, use 
                   curly braces {}. */
  double _d;
  std::string _s;

  Foo(const int i, const double d,
      const std::string& s);  // custom constructor

  Foo();  // default constructor (is this line necessary?)

  ~Foo();  // destructor
};

Foo::Foo(const int i, const double d, const std::string& s)
    : _i{i},  // construct and initialize at the same time (fast!--> PREFERRED)
      _d{d},
      _s{s}
// _i, _d, _s must be initialized in the same order they have been declared

{
  /* Writing "_i{i}"" here would cause an error, because it has already been 
     initialized. You could instead write here _i = i; but it it slower than the
     combined construction & initialization operation _i{i} above. */ 
  std::cout << "custom ctor\n";
  // if you want/need you can use _i, _d, _s and change their value
  // with the usual notation +,-,=,*, call a function..
  // don't use {} because this notation is reserved for the
  // construction of the variables and at this point they have already
  // been constructed
}

Foo::Foo() {
  std::cout << "default ctor\n";  // what happens to our member variables?
}

Foo::~Foo() {
  std::cout << "dtor\n";
}

/* This defines an overloaded operator. It must be defined outside the class!
   Why do we need std::ostream& here? See later lecture! */
std::ostream& operator<<(std::ostream& os, const Foo& f) {
  // "os" is a fully qualified name of the same usage as std::cout
  os << f._i << " " << f._d << " " << f._s << std::endl;
  return os;
}

int main() {
  Foo f0;    // call default ctor
  Foo f1{};  // call default ctor  // "{}" is uniform and universal!
  // Foo f2(); // compiler error. Why? "()" are not clearly defined here!

  Foo f2{8, 2.2, "hello"};  // These are the three arguments of the default 
                            // constructor
  /* "<< f0" in the following line means "add another argument to the function
     std::cout, and insert the string content of the object os" */
  std::cout << "f0: " << f0 << "f1: " << f1 << "f2: " << f2 << std::endl;

  // the destructor is called when the variable goes out of scope.
  /* A destructor "destroys" (disallocates) the elements of a class object
     in the inverse order compared to the constructor.
     IMPORTANT: Never invoke a destructor by hand! */
  return 0;
}
