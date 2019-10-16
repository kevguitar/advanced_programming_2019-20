#include <iostream>
#include <string>

// Write a code that reads a number with its proper unit of measure, and prints 
// back that number according to the SI units, e.g.
//
// ```
// 1 inch
// 0.0254 m   
// ```


/*double operator"" _m(long double x) { return double(x); 
}
double operator"" _m(unsigned long long int x) { return double(x); 
}
double operator"" _inch(long double x) { return double(x) * 0.0254;
}*/

int main() {
  double value;
  std::string unit;

  std::cin>>value;
  
  while (std::cin.fail()) {
      // std::cout<<"Wrong input! You have to provide a double."
      //          <<std::endl;
      std::cin.clear();
      std::cin.ignore();
      std::cin>>value;
  } 

  std::cin>>unit;
  while (std::cin.fail()) {
      // std::cout<<"Wrong input! You have to provide a string."
      //          <<std::endl;
      std::cin.clear();
      std::cin.ignore();
      std::cin>>unit;
  } 

  //std::cout<<"value = "<<value<<", unit = "<<unit<<std::endl;

  if (unit=="m") {}
  else if (unit=="inch") { value = value*0.0254; }
  else if (unit=="ft") { value = value*0.3048; }
  else if (unit=="yd") { value = value*0.9144; }
  else if (unit=="km") { value = value*1000; }
  else if (unit=="mi") { value = value*1609.34; }
  else if (unit=="pc") { value = value*3.086e+16; }


  std::cout<<value<<" m"<<std::endl;

  return 0;
}
