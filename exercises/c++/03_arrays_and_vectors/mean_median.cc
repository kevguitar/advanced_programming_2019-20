#include<iostream>
#include<string>
#include<fstream>  // read string from file
#include<vector>
#include<algorithm>  // std::sort(v.begin(), v.end());


template <typename T>
void store_numbers(std::vector<T>& v, const std::string& filename);

template <class T>
double median(std::vector<T>& v);

template <class T>
double mean(std::vector<T>& v);

int main() {
  std::vector<double> temps;
  store_numbers<double>(temps, "temperatures.txt");

  std::cout<<"median = "<<median(temps)<<std::endl;
  std::cout<<"mean = "<<mean(temps)<<std::endl;

  // DEBUG
  std::cout<<"length = "<<temps.size()<<std::endl;
  for (auto x : temps) std::cout<<x<<std::endl;

  return 0;
}

template <typename T>
void store_numbers(std::vector<T>& v, const std::string& filename) {
  double temp;
  std::ifstream inFile;
  inFile.open(filename);

  if (!inFile) {
    std::cerr << "Unable to open file "<<filename;
    exit(1);   // call system to stop
  }

  while(inFile>>temp) v.push_back(temp);

  inFile.close();
}

template <class T>
double median(std::vector<T>& v) {
  std::sort(v.begin(), v.end());
  
  if (v.size()%2==0)
    return 0.5*(v[v.size()/2] + v[v.size()-1]);
  else return v[v.size()/2+1];
}


template <class T>
double mean(std::vector<T>& v) {
  double sum{0};
  for (auto x : v) sum += x;
  
  return sum/v.size();
}