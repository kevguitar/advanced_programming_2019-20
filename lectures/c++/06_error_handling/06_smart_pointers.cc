#include <iostream>
#include <memory>  // std::uniqe_ptr
#include <cmath>   // sqrt

#include "ap_error.h"

class Vector {
  std::unique_ptr<double[]> elem;  /* This includes error handling if sth fails
                                      during stack unwinding. */

 public:
  Vector(const unsigned int l) : elem{new double[l]} {
    std::cout << "Vector ctor\n";
  }
  /* "noexcept": compiler flag to tell the compiler not to throw an exception. 
     Attention: If this is done, there will be no notifications when failure! */
  double& operator[](const unsigned int i) noexcept {
    return elem[i];
  }  // you can use smart pointers almost like raw pointers
  ~Vector() noexcept { std::cout << "~Vector\n"; }
};

class ManyResources {
  std::unique_ptr<double[]> ptr;
  Vector v;

 public:
  ManyResources() : ptr{new double[5]}, v{3} {
    std::cout << "ManyResources ctor\n";
    //AP_ERROR(false) << "I am simulating something wrong.\n";
  }
  ~ManyResources() noexcept { std::cout << "~ManyResources\n"; }
};

int main() {
  try {
    /* int* up{new int[7]}; // warning: unused variable ‘up’ [-Wunused-variable] 
                         //                and memory leak produced */  
    std::unique_ptr<int[]> up{new int[7]}; 
                                           /* Here, defining the pointer inside
                                              the try-block is no problem, since
                                              the constructor of the class
                                              std::unique_ptr is responsible for
                                              cleaning the memory. */
    ManyResources mr;

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;
    return 2;
  }

  return 0;
}
