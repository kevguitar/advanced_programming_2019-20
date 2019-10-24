#include <array>
#include <iostream>
#include <vector>

<<<<<<< HEAD

// structs in C++ CAN have variables AND functions!
struct Point_s {
  double x;
  double y;
  void print();        // function declaration inside a struct
};  // note ; at the end

void Point_s::print() {  // function definition outside a struct
  std::cout << "Structure. x = " << x << "; y = " << y << std::endl;
}


// classes in C++ are basically struct, except for the following differences
class Point_c {
  double x;
  double y;

// default: private (not visible in outside scope)
 public:
  void print() {      // function declaration and initialization inside class,
                      // (but one can always define it outside the class)
    std::cout << "Class. x = " << x << "; y = " << y << std::endl;
  }  // note no ; at the end
};   // note ; at the end
// Remember: All the member functions of a class can access all its symbols! 


int main() {
  Point_s ps;
  ps.x = 9.9;
  ps.y = 3. / 7;

  ps.print();

  Point_c pc;
  // pc.x =7.6; // error
  pc.print();  // I can access private data through public functions

<<<<<<< HEAD
  Point_s* p = &ps;   // pointer to a class
  p->x = 0.0;         // assign to the element x of the object ps the value 0.0
  p->print();

  auto& pr = ps;    // creates reference "pr" of the object ps 
  ++pr.x;           // increment element x of object ps 
  pr.print();       // equivalent to ps.print()

  Point_s array_of_structs[8];  // built-in array of objects of struct Point_s
  array_of_structs[0].x = 1;
  array_of_structs[0].y = 2;

  std::array<Point_s, 5> as;    // std::array of objects of struct Point_s
  as[3].x = 3;

  std::vector<Point_s> vs;    // std::vector of objects of struct Point_s
  vs.push_back(ps);           // creates a copy of ps and puts it inside of vs

  vs[0].x = 999;
  ps.x = 11;
  ps.print();
  vs[0].print();

  // How is the initialization of std::vector<Point_s> is possible without
  // memory leaks? Solution: constructor and destructor operators!

  // Open questions: 
  // 1) Why does it still work with Point_s, which has no 
  //    apparent constructor?
  // 2) Is there a "default constructor" implemented automatically in every 
  //    struct? 

  return 0;
}
