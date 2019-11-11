#include <iostream>
#include <vector>
#include <string>


enum class months { jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, 
                    dec };

// prefix increment months (copy overload)
months& operator++(months& m) {
  //std::cout<<"months - copy inc"<<std::endl;
  if (m==months::dec) m = months::jan; 
  else m = static_cast<months>(static_cast<int>(m) + 1);
  return m;
}

// prefix increment months (move overload)
months& operator++(months&& m) {
  //std::cout<<"months - move inc"<<std::endl;
  if (m==months::dec) m = months::jan; 
  else m = static_cast<months>(static_cast<int>(m) + 1);
  return m;
}



class Date {
 private:
  unsigned int _day, _year;
  months _month;

  // (decl only)
  void increment();

 public:
  // default ctor
  Date(unsigned int d, unsigned int y, months m) 
      : _day{d}, _year{y}, _month{m} {};
  ~Date() = default;
  unsigned int day() const { return _day; }  /* "const" needed to mark 
                                                "day()" a "safe" function. */    
  months month() const { return _month; }
  unsigned int year() const { return _year; }

  void print() { 
    std::cout<<_day<<"/"<<static_cast<int>(_month)+1<<"/"<<_year<<std::endl; 
  }
  void add_days(const unsigned int n) { for (int i{0}; i<n; ++i) increment(); }
};

bool operator==(const Date& lhs, const Date& rhs) {
  bool d{lhs.day()==rhs.day()}, m{lhs.month()==rhs.month()}, 
       y{lhs.year()==rhs.year()};
  return (d && m && y);
}

bool operator!=(const Date& lhs, const Date& rhs) {
  return !(lhs==rhs);
}

std::ostream& operator<<(std::ostream& os, const Date& d) {
  os<<d.day()<<"/"<<static_cast<int>(d.month())+1<<"/"<<d.year()<<std::flush;
  return os;
}


int main() {
  Date d1{24, 2019, months::dec};
  Date d2{d1};
  std::cout<<"d1 = "<<d1<<", d2 = "<<d2<<std::endl;
  std::cout<<"(d1==d2) = "<<(d1==d2)<<std::endl;
  std::cout<<"(d1!=d2) = "<<(d1!=d2)<<std::endl;
  
  d1.add_days(365);
  std::cout<<"d1 = "<<d1<<", d2 = "<<d2<<std::endl;
  std::cout<<"(d1==d2) = "<<(d1==d2)<<std::endl;
  std::cout<<"(d1!=d2) = "<<(d1!=d2)<<std::endl;

  return 0;
}



void Date::increment() {
  switch(_month){
    case months::jan: case months::mar: case months::may: case months::jul: 
    case months::aug: case months::oct:
      if (_day==31) { 
        _day = 1; 
        ++_month;
      } else ++_day;
      break;
    case months::apr: case months::jun: case months::sep: case months::nov:
      if (_day==30) {
        _day = 1;
        ++_month;
        
      } else ++_day;
      break;
    case months::feb:
      if (_day==28) {
        _day = 1;
        ++_month;
        
      } else ++_day;
      break;
    case months::dec:
      if (_day==31) {
        _day = 1;
        ++_month;
        ++_year;
      } else ++_day;
      break;
    default:
      std::cout<<"Error in date format."<<std::endl;
      break;
  }
}

