#include<iostream>
#include<iomanip> // std::setw(std::size_t width)
#include<array>
#include<utility>   // std::swap
#include<sstream>   // read content from string


template <typename T> 
T matrix_transpose(const T& original, std::size_t rows, std::size_t cols);

template <typename T> 
void print_matrix(const T& matrix, std::size_t rows, std::size_t cols);


int main(int argc, char* argv[]) {
  if (argc!=3) {
    std::cerr<<"There is a problem with input arguments.";
    return 1;
  }
  std::size_t tmp[2];
  for (auto i{0}; i<2; ++i) {
    std::istringstream is{argv[i+1]};
    is>>tmp[i];     // istringstream has an overloaded ">>" to size_t
  }
  std::size_t r{tmp[0]}, c{tmp[1]};
  std::cout<<"rows = "<<r<<", cols = "<<c<<std::endl;

  std::array<int, 9> matrix{1,2,3,4,5,6,7,8,9};
  std::cout<<"original matrix:"<<std::endl;
  print_matrix(matrix, r, c);
  auto matrix_t = matrix_transpose(matrix, r, c);
  std::cout<<"transposed matrix:"<<std::endl;
  print_matrix(matrix_t, c, r);

  return 0;
}

template <typename T> 
T matrix_transpose(const T& original, std::size_t rows, std::size_t cols) {
  T modified{original};
  std::size_t rx{0};
  for (; rx<rows; ++rx) {
    for (auto cx{rx}; cx<cols; ++cx) {
      std::swap(modified[rx*cols + cx], modified[cx*rows + rx]);
    }
  }

  return modified;
}

template <typename T> 
void print_matrix(const T& mat, std::size_t rows, std::size_t cols) {
  for (std::size_t rx{0}; rx<rows; ++rx) {
    for (std::size_t cx{0}; cx<cols; ++cx) {
      std::cout<<std::setw(2)<<mat[rx*cols + cx]<<" ";
    }
    std::cout<<std::endl;
  }
}