#include <iostream>
#include <vector>
#include <string>


enum class months { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, 
                    dec };

class Date {
 private:
  unsigned int _day, _year;
  months _month;
  void increment();

 public:
  Date(unsigned int d, unsigned int y, months m);
  ~Date();
  unsigned int day() { return _day; }
  months month() { return _month; }
  unsigned int year() { return _year; }
  void add_days(const unsigned int n);
};

Date::Date(unsigned int d, unsigned int y, months m) 
    : _day{d}, _year{y}, _month{m} {
  std::cout<<"Construct 'Date'..."<<std::endl;
}

Date::~Date() {
  std::cout<<"Destruct 'Date'..."<<std::endl;
}

void Date::increment() {
  // TODO: Implement overloaded operator++ for months!
  switch(_month){
    case months::jan: case months::mar: case months::may: case months::jul: 
    case months::aug: case months:oct:
      if (_day==31) { 
        _day = 1; 
        _month++; // TODO!!
      } else _day++;
    case months:apr: months::jun: months::sep: months::nov:
      if (_day==30) {
        _day = 1;
        _month++; // TODO!!
      } else _day++;
    case months::feb:
      if (day==28) {
        _day = 1;
        _month++;
      } else _day++;
    case months::dec:
      if (day==31) {
        day = 1;
        _month = months::jan;
        }
      }

  }

}

void Date::add_days(const unsigned int n) {
  for (int i{0}; i<n; ++i) increment();
}

void 


int main() {
  Date xmas{24, 2019, months::dec};
  //xmas.increment();
  xmas.add_days(4);
  int m{static_cast<int>(xmas.month())};
  std::cout<<"xmas.month() = "<<m<<std::endl;

  return 0;
}


/*
int a;
...
switch (a){
  case 0: case 2: case 4:
  case 6: case 8: case 10:
    std::cout << "a is even\n";
    break;

  case 1: case 3: case 5:
  case 7: case 9:
    std::cout << "a is odd\n";
    break;
  default:
    std::cout << "a > 10\n";
    break;
}
*/