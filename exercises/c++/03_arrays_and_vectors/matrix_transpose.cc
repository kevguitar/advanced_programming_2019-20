#include<iostream>
#include<iomanip> // std::setw(size_t width)
#include<array>
#include<utility>   // std::swap


// pass argument of type T by reference
template <typename T> 
T transpose_matrix(const T& original, const size_t rows, const size_t cols) {
  // initialize modified and set it equal to original  
  T modified{original};


  // TODO:
  // The arguments of std::swap are not accepted; need to replace them by the
  // correct formulation.
  for (size_t i=0; i<rows; ++i) {
    for (size_t j=i; j<cols; ++j) {
      // Swaps the values assigned to the addresses corresponding to the 
      // (i,j) element and the (j,i).
      std::swap(*(&original + i*cols + j), *(&original + j*cols + i));
    }
  }
  return modified;
}

int main() {
  const size_t N{9};
  std::array<int, N> matrix{1,2,3,4,5,6,7,8,9}; 
  //std::array<int, N> matrix_t;    // not needed, since auto can be used

  for (const auto x : matrix) 
    std::cout<<std::setw(3)<<x<<" ";
  std::cout<<std::endl;
    
  auto matrix_t = transpose_matrix(matrix, 3, 3);

  for (const auto x : matrix_t) 
    std::cout<<std::setw(3)<<x<<" ";
  std::cout<<std::endl;


  return 0;
}

