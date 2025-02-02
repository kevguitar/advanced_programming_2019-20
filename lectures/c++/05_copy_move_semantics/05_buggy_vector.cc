#include <iostream>
#include <memory>

template <typename T>
class Vector {
  std::unique_ptr<T[]> elem;
  std::size_t _size;

 public:
  /* Not initializing the elements, we construct a vector with elements all
     equal to zero. */
  explicit Vector(const std::size_t length)
      : elem{new T[length]{}}, _size{length} {}

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return elem.get(); }
  T* begin() { return elem.get(); }

  const T* end() const { return elem.get() + _size; }
  T* end() { return elem.get() + _size; }
};

int main() {
  Vector<double> v1{7};
  
  std::cout << "v1: ";
  for (const auto x : v1)
    std::cout << x << " ";
  std::cout << std::endl;

  // Vector<double> v2{v1}; // default copy ctor calls a deleted function by
                            // std::unique_ptr
  return 0;
}
