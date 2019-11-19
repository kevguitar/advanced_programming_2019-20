#include <iostream>
#include <vector>

#include "ap_error.h"

/* When an exception is thrown, the compiler has to unwind the stacks 
   corresponding to different layers of code.
  To check for memory leaks, type:
  valgrind --leak-check=yes ./05_stack_unwinding.x
*/

class Foo {
 public:
  Foo() { std::cout << "Foo" << std::endl; }
  ~Foo() { std::cout << "~Foo" << std::endl; }
};

class Bar {
 public:
  Bar() { std::cout << "Bar" << std::endl; }
  ~Bar() { std::cout << "~Bar" << std::endl; }
};

class Vector {
  double* elem;

 public:
  Vector(const unsigned int l) : elem{new double[l]} {
    std::cout << "Vector" << std::endl;
  }
  ~Vector() noexcept {
    delete[] elem;
    std::cout << "~Vector" << std::endl;
  }
};

class ManyResources {
  double* ptr;
  Vector v;

 public:
  ManyResources() : ptr{nullptr}, v{3} {
    std::cout << "Manyresources" << std::endl;
    try { // new will throw 
      ptr = new(std::nothrow) double[5];  // new(std::nothrow) double[5] could be better
      AP_ERROR(false) << "Error in ManyResources ctor." << std::endl;
    } catch (...) {
      delete[] ptr;  // <----
      throw;  // This is a rethrow of whatever has been thrown inside catch.
    }
  }

  ~ManyResources() noexcept {
    std::cout << "Manyresources" << std::endl;
    delete[] ptr;  // <----
  }
};

int main() {
  Foo f;

  /* Have to call raw_ptr outside the try block, since we want to execute 
     delete[] raw_ptr outside. */
  int* raw_ptr = new int[7];

  /* Do not use raw pointers, since they produce memory leaks. Instead, use 
     smart pointers, e.g. unique_ptr<typename>, shared_ptr<typename>. */
  try {
    // int * raw_ptr=new int[7]; // wrong because raw_ptr would not be visible
    // inside the catch-clause
    ManyResources mr;
    Bar b;

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;

    delete[] raw_ptr;  // <--- try to comment this and run valgrind or use the
                       // sanitize library
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;

    delete[] raw_ptr;  // <---
    return 2;
  }

  delete[] raw_ptr;  // <---
  return 0;

  // TODO: execute this script to see:
  // - when which constructor and destructor is called
  // - when an exception is thrown
}
