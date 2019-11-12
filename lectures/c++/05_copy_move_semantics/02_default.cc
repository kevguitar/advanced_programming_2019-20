#include <iostream>
#include <string>

struct S {
  int a;
  double b;
  std::string s;  // default ctor of string set s to empty string
};

int main() {
  S s1;  // calls default constructor: The constructor that would be envoked
         // without giving any arguments

  S s2{1, 2.3, "alberto"};  // if there are no custom ctors I can
                            // directly initialize the members. Note
                            // that I need access (i.e. they must be
                            // public)
  // it is called aggregate initialization (see
  // https://en.cppreference.com/w/cpp/language/aggregate_initialization)
  /* Attention: The behavior of aggregate initialization changes wildly from
                version to version */

  S s3{};  // calls {} on each member: S s3 { {}, {}, {} };

  /* s1.a is a random int, s1.b is a random double, s1.c is an empty string 
     (by default)
     s2.a = 1, s2.b = 2.3, s2.c = "alberto"
     s3.a = 0, s2.b = 0, s3.c = "" (empty string)
  */ 
  std::cout << s1.a << "--" << s1.b << "--" << s1.s << "\n";
  std::cout << s2.a << "--" << s2.b << "--" << s2.s << "\n";
  std::cout << s3.a << "--" << s3.b << "--" << s3.s << "\n";

  return 0;
}
