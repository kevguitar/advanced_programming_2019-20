/*Modify the class `Vector<typename T>` presented during the lecture exploiting 
all the of C++14 features you know:
* auto [type specifier] for function return types and lambda expressions 
  (since C++14)
* unique_ptr<typename> (since C++11)
* enum class (since C++11)
* std::move (since C++11)
* template<class T> class std::initializer_list (since C++11)
* aggregate initialization T object {arg1, arg2, ...}; (since C++11)
* auto glambda = [](auto a, auto&& b) { return a < b; }; (since C++14)
* for (const auto x : v1) {...}  (since C++11)

Can you see any benefit?

*Hints*:

- remember to compile with `-std=c++14`*/


#include <iostream>
#include <string>

template <typename num>
class Vector {
  num* elem;
  std::size_t _size;

 public:
  /* Warning: narrowing conversion of ‘(int)size’ from ‘int’ to ‘std::size_t 
     {aka long unsigned int}’  */
  /*Vector(const auto size) : elem{new num[size]}, _size{size} {}*/
  Vector(const std::size_t size) : elem{new num[size]}, _size{size} {}

  ~Vector() { delete[] elem; }

  std::size_t size() const { return _size; }

  num& operator[](const auto i) { return elem[i]; }
  const num& operator[](const auto i) const { return elem[i]; }
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (auto i = 0u; i < v.size(); ++i)
    os << "v[" << i << "] = " << v[i] << std::endl;
  return os;
}


int main() {
  Vector<double> v{10};

  for (auto i = 0u; i < v.size(); ++i)
    v[i] = i;

  std::cout << v << std::endl;

  Vector<double>* pv{&v};

  /* Tricky (ugly!): dereference overloaded operators. */
  
  // first dereference the pointer, then I can use the defined operators
  (*pv)[0] = -99.999;

  pv->operator[](1) = 77777.3333;  // or I call the function by name

  std::cout << *pv << std::endl;

  Vector<double>& rv{v};

  rv[5] = 555;

  std::cout << v << std::endl;

  return 0;
}
