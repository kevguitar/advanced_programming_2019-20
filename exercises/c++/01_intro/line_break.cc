#include <iostream>
#include <string>

// Write a simple text formatter that breaks the lines longer than a given 
// number of characters. This formatter does not break words.


int main() {
  std::string line;
  std::string word;
  unsigned int number;
  long unsigned int count;
  // std::cout<<"Insert a number defining the maximum number of characters per line."
  //          <<std::endl;
  // std::cin>>number;
  number = 12;

  //std::cout<<"Insert a text to be formatted."<<std::endl;
  std::cin>>line;

  while (line.length() < number) {
    std::cin>>word;
    if (!std::cin) {
      std::cout<<line<<std::endl;
      break;
    }
    count = line.length() + 1 + word.length();
    if (count < number) { 
      line = line + " " + word; 
    } else {
      std::cout<<line<<std::endl;
      line = word;
    }
  }

  return 0;
}
