#include <iostream>
#include <string>

// Write a function `get_int` that reads from stdin until a valid number is fed.

int main() {
  int n;
  std::cin>>n;
  
  while (true) {
    if (std::cin.fail()) {
      std::cout<<"Wrong input! You have to provide an integer number."
               <<std::endl;
      std::cin.clear();
      std::cin.ignore();
      std::cin>>n;
    }
    else {
      std::cout<<"Correct input! n="<<n<<std::endl;
      return 0;
    }  
    
  }

}
