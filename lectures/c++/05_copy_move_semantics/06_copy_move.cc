#include <algorithm>  // std::copy
#include <iostream>
#include <memory>

template <typename T>
class Vector {
  std::size_t _size;
  std::unique_ptr<T[]> elem;

 public:
  // custom ctor
  explicit Vector(const std::size_t length)
      : _size{length}, elem{new T[length]{}} {
    std::cout << "custom ctor\n";
  }

  // Vector(const std::initializer_list<T> args)
  //     : _size{args.size()}, elem{new T[_size]} {
  //   std::cout << "list ctor\n";
  //   std::copy(args.begin(), args.end(), begin());
  // }

  // default ctor
  Vector() { std::cout << "default ctor\n"; }  // _size uninitialized
  // Vector() : _size{}, elem{} { std::cout << "default ctor\n"; } // this could
  // be better Vector() = default; /* What does he mean by this? */

  ~Vector() = default;

  /////////////////////////
  // copy semantics

  // copy ctor -- deep copy
  Vector(const Vector& v);

  // copy assignment -- deep copy
  Vector& operator=(const Vector& v);
  // end of copy semantics
  /////////////////////////

  /////////////////////////
  // move semantics

  // move ctor
  /* Vector&& v is an rvalue, since it has no function on the lhs of an equation
     std::move takes the vector v itself (no copy) */ 
  Vector(Vector&& v) : _size{std::move(v._size)}, elem{std::move(v.elem)} {
    std::cout << "move ctor\n";
  }

  // Vector(Vector&& v) = default; // ok 
      /* --> Compiler understands to use std::move in initializer */ 

  // move assignment
  Vector& operator=(Vector&& v) {
    std::cout << "move assignment\n";
    _size = std::move(v._size);
    elem = std::move(v.elem);
    /* *this gives the instantiation of the class (the object). */
    return *this;
  }

  // Vector& operator=(Vector&& v) = default; // ok
      /* --> Compiler understands to use std::move in move assignment */ 

  // end move semantics
  /////////////////////////

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return &elem[0]; }
  T* begin() { return &elem[0]; }

  const T* end() const { return &elem[_size]; }
  T* end() { return &elem[_size]; }
};

// copy ctor
template <typename T>
Vector<T>::Vector(const Vector& v) : _size{v._size}, elem{new T[_size]} {
  std::cout << "copy ctor\n";
  /* How does std::copy act on the memory? */
  std::copy(v.begin(), v.end(), begin());
}

// copy assignment
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& v) {

  // Value of this is the address of the very same object.
  if (&v == this)
    return *this;

  std::cout << "copy assignment (\n";

  // we could decide that this operation is allowed if and only if
  // _size == v._size
  //

  elem.reset();              // first of all clean my memory
  auto tmp = v;              // then use copy ctor
  (*this) = std::move(tmp);  // finally move assignment

  // or we do everything by hand..
  // and we can do not reset and call new again if the sizes are suitable

  std::cout << ")\n";
  return *this;

  // is this approach consistent with self-assignment vx=vx?
}

template <typename T>
// why we return by value?
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
  const auto size = lhs.size();

  // how we should check that the two vectors have the same size?
  /* We do not check here, do we ? If rhs has less elements than lhs, error!? */

  Vector<T> res(size);
  for (std::size_t i = 0; i < size; ++i)
    res[i] = lhs[i] + rhs[i];

  return res;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (const auto& x : v)
    os << x << " ";
  os << std::endl;
  return os;
}

int main() {
  std::cout << "Vector<int> v0; calls\n";     /* default ctor */
  Vector<int> v0;
  std::cout << v0.size() << "\n";             /* random size_t */
  std::cout << "Vector<int> v00{}; calls\n";  /* default ctor */
  Vector<int> v00{};    
  std::cout << v00.size() << "\n";            /* another random size_t */

  std::cout << "\nVector<double> v1{5}; calls\n";   /* custom ctor */
  Vector<double> v1{5};  /* This involves the list initializer {value1, value2, ...} */
  /*std::cout << "\nVector<double> v1a(4); calls\n";
  Vector<double> v1a(4,2); /* This invokes the size initializer. (size, value) */

  std::cout << "\nVector<double> v2 = v1; calls\n";  /* copy ctor */
  Vector<double> v2 = v1;
  std::cout << "\nv2 = Vector<double>{7}; calls\n";  /* custom ctor;
                                                        move assignment    */
  v2 = Vector<double>{7};
  std::cout << "\nVector<double> v3{std::move(v1)}; calls\n";  /* move ctor */
  Vector<double> v3{std::move(v1)};  // now v1 should not be used
  std::cout << "\nv3 = v2; calls\n";   /* copy assignment ( copy ctor, 
                                                            move assignment ) */
  v3 = v2;
  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

  std::cout << "\nassign some values to v3\n";
  {
    // auto i = v3.size();
    // while (i--)
    //   v3[i] = i;

    int c = 0;
    for (auto& x : v3)
      x = c++;
  }
  // v3=v3;
  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

  std::cout << "\nVector<double> v4{v3 + v3}; calls\n";  /* custom ctor */
  Vector<double> v4{v3 + v3};

  std::cout << "v4 = " << v4;

  std::cout << "\nNRVO: Named Return Value Optimization\n";

  std::cout << "\nv4 = v3 + v3 + v2 + v3; calls\n";  /* custom ctor (3x)
                                                        move assignment */
  v4 = v3 + v3 + v2 + v3;
  std::cout << "v4 = " << v4;

  return 0;
}
