#include <iostream>
#include <string>

// Write a code that reads a number with its proper unit of measure, and prints 
// back that number according to the SI units, e.g.
//
// ```
// 1 inch
// 0.0254 m
// ```

int main() {
  double x;
  std::cin>>x;
  
  while (true) {
    if (std::cin.fail()) {
      std::cout<<"Wrong input! You have to provide a double floating point number."
               <<std::endl;
      std::cin.clear();
      std::cin.ignore();
      std::cin>>x;
    }
    else {
      std::cout<<"Correct input! x="<<x<<std::endl;
      return 0;
    }  
    
  }

}
