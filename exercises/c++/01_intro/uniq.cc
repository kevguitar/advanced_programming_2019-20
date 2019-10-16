#include <iostream>
#include <string>

// Write a program that, when fed with a text, outputs the same text with 
// adjacent identical lines collapsed into one, and displays the number of
// occurences of every line on its left hand side, respectively.

int main() {
  std::string line;
  std::string old_line;
  std::string new_line;
  unsigned int count;

  std::getline(std::cin, line);
  old_line = line;
  count = 1;

  /* While-loop seems to be slightly preferrable w.r.t. for-loop since string 
    'line' does not need to be initialized every time. */

  //for (std::string line; std::getline(std::cin, line);) {
  while (std::getline(std::cin, line)) {  
    new_line = line;
    if (new_line == old_line) {
      count++;
    } else {
      std::cout<<count<<" "<<old_line<<std::endl;
      count = 1;
      old_line = new_line; 
    }
  }
  std::cout<<count<<" "<<new_line<<std::endl;

  return 0;
}
