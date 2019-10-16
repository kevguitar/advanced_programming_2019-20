#include<iostream>

/*template: allocate on the heap one array of a given size,
          initialize its elements, returns the pointer to the first element.
          (use size_t)*/




// /* template: print_elements (first integers, then doubles) in reverse order */
// template <typename T> 
// T print_reverse(T* first_element, size_t size) {
//   for (std::size_t i{size})
//   std
// }

template <typename T>
T allocate(size_t size);

int main()
{
  size_t number;
  std::cout<<"Insert size: "<<std::endl;
  std::cin>>number;

  std::cout<<"Insert array of size "<<number<<std::endl;

  int value;
  // Should return the value of the first element of the array.
  value = allocate<int>(number);
  std::cout<<"value = "<<value<<std::endl;

  int* address;
  // Should return the address of the first element of the array.
  address = &allocate<int>(number);
  std::cout<<"address = "<<address<<std::endl;


  return 0;
}



template <typename T>
T allocate(size_t size) {
  T* T_array{new T[size]}; // allocate

  for (std::size_t i{0}; i < size; ++i) {
    T element;                // initialize
    std::cin>>element;
    T_array[i] = element;
  }
  T address{T_array[0]};

  return address;   
}




