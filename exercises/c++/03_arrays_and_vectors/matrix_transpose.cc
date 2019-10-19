#include<iostream>
#include<iomanip> // std::setw(std::size_t width)
#include<array>
#include<utility>   // std::swap
#include<sstream>   // read content from string


template <typename T> 
T matrix_transpose(const T& original, std::size_t rows, std::size_t cols);

template <typename T> 
T swap_example(const T& original);

template <typename T> 
void print_matrix(const T& matrix, std::size_t rows, std::size_t cols);


int main(int argc, char* argv[]) {
  // First version: No command line arguments.
  /*const std::size_t c{3};
  const std::size_t r{3};*/

  // Second version: command line arguments
  std::size_t args[2];
  for (auto i{0}; i<2; ++i) {
    std::istringstream is{argv[i+1]};
    is>>args[i];
  }
  std::size_t r{args[0]}, c{args[1]};
  std::cout<<"rows = "<<r<<", cols = "<<c<<std::endl;

  // An array size must be known at compile time, so no variable here.
  std::array<int, 9> matrix {1,2,3,4,5,6,7,8,9};
  //std::array<int, N> matrix_t;    // not needed, since auto can be used
  std::cout<<"original matrix:"<<std::endl;
  print_matrix(matrix, r, c);
  auto matrix_t = matrix_transpose(matrix, r, c);
  std::cout<<"transposed matrix:"<<std::endl;
  print_matrix(matrix_t, r, c);

  return 0;
}

template <typename T> 
T swap_example(const T& original) {
  T modified{original};
  std::swap(modified[0], modified[1]);

  return modified;
}

template <typename T> 
T matrix_transpose(const T& original, std::size_t rows, std::size_t cols) {
  T modified{original};
  std::size_t rx{0};
  for (; rx<rows; ++rx) {
    for (auto cx{rx}; cx<cols; ++cx) {
      std::swap(modified[rx*rows + cx], modified[cx*rows + rx]);
    }
  }

  return modified;
}

template <typename T> 
void print_matrix(const T& mat, std::size_t rows, std::size_t cols) {
  std::size_t rx{0};
  for (; rx<rows; ++rx) {
    for (std::size_t cx{0}; cx<cols; ++cx) {
      std::cout<<std::setw(2)<<mat[rx*rows + cx]<<" ";
    }
    std::cout<<std::endl;
  }
}