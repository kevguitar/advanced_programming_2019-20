#include <iostream>

template <typename T>
class Vector {
  T* elem;
  std::size_t _size;

 public:
  /* "explicit" means not to invoke the default constructor.
     "new T[length]" initialized array in the heap
     without the last {}, we would get "error: malloc"
  */   

  /* Must include this explicit constructor, because default constructor needs
    two arguments (not one, as given in main()). */
   /*explicit*/ Vector(const std::size_t length)
      : elem{new T[length]{}}, _size{length} {}

  ~Vector() { delete[] elem; }

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  /* This enables me to invoke "auto" to instatiations of the class. */
  const T* begin() const { return elem; }
  T* begin() { return elem; }

  const T* end() const { return elem + size(); }
  T* end() { return elem + size(); }
};

int main() {
  Vector<int> v1{4};

  // "Vector<int> v1;" here invokes a segmentation fault!
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;
  v1[3] = 4;
  std::cout<<"check"<<std::endl;

  std::cout << "v1: ";
  for (const auto x : v1)
    std::cout << x << " ";
  std::cout << std::endl;

  Vector<int> v2{v1};  // default copy constructor

  std::cout << "v2 after default copy ctor: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v1[0] = 99;

  std::cout << "v2 after v1 has been changed: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v2[1] = -999;


  /* v1 will have elements {99, -999, 3}, not {99, 2, 3}. */
  std::cout << "v1 after v2 has been changed: ";
  for (const auto x : v1)
    std::cout << x << " ";
  std::cout << std::endl;

  return 0;
}
