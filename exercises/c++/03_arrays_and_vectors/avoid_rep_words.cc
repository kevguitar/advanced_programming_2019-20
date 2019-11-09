/*## Avoid repeated words

- Read from stdin a sequence of words. Store each word in a 
  `std::vector<std::string>`. Then, print the words without repetitions.

*Hints*:

- you can print the words in any order you want (i.e., you are not required to 
  print the words in the order you have read them)*/

#include<iostream>
#include<string>
#include<fstream>  // read string from file
#include<vector>
#include<set>      // container with unique elements 


void read_words(std::vector<std::string>& words, 
                const std::string& filename);

template <class T>
void print_con(const T& c, const std::string& s);


int main() {
  std::vector<std::string> w;
  read_words(w, "LittleWomen.txt");
  std::set<std::string> s(w.begin(), w.end());

  //print_con(w, "old vector");
  print_con(s, "\nnew vector");

  std::cout<<"w.size() = "<<w.size()<<std::endl;
  std::cout<<"s.size() = "<<s.size()<<std::endl;

  return 0;
}


void read_words(std::vector<std::string>& words, const std::string& filename) {
  std::ifstream inFile;
  inFile.open(filename);
  if (!inFile) {
    std::cerr << "Unable to open file "<<filename;
    exit(1);   // call system to stop
  }
  std::string w;
  while (inFile>>w)    // reads words by ifstream
    words.push_back(w);
  inFile.close();
}

template <class T>
void print_con(const T& c, const std::string& s){
  std::cout<<s<<":"<<std::endl;
  for (auto x : c)
    std::cout<<x<<" "<<std::flush;
}
