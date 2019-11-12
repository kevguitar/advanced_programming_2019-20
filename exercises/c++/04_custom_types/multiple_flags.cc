#include <iostream>

// Declares an unscoped enumeration type whose underlying type is fixed.
enum class flags : unsigned int {
  /* Since enum classes do not implicitly convert to integers, this code does 
     not compile. */ 
  flag1 = 1,
  flag2 = 2,
  flag3 = 4,
  // flag4 = 8 | flag1 | flag2, // imply flag1 and flag2 easy to implement, but
  // difficult to compare..
  flag4 = 8,   // additional functions needed
  flag5 = 16,  // imply flag3

  // useful combinations
  comb1 = flag1 | flag2,
  comb2 = flag1 | flag3,
  comb3 = comb1 | flag3,
};

void do_complicated_stuff(flags f);

flags operator|(const flags f1, const flags f2);

unsigned int operator&(const flags f1, const flags f2);

flags& operator|=(flags& f1, const flags f2);

int main() {
  std::cout << "testing flag1 and flag3\n"
            << "expected  flag1 and flag3 \n\n";
  do_complicated_stuff(flags::flag1 | flags::flag3 | flags::flag1 |
                       flags::flag1);

  std::cout << "--------------\n\n"
            << "testing comb3\n"
            << "expected  flag1, flag2 and flag3 \n\n";
  do_complicated_stuff(flags::comb3);

  std::cout << "--------------\n\n"
            << "testing flag4\n"
            << "expected  flag1, flag2 and flag4 \n\n";
  do_complicated_stuff(flags::flag4);

  std::cout << "--------------\n\n"
            << "testing flag5\n"
            << "expected flag3 and flag5 \n\n";
  do_complicated_stuff(flags::flag5);

  return 0;
}

// A bitwise | operator is missing, so we have to define our own one.
flags operator|(const flags f1, const flags f2) {
  return static_cast<flags>(static_cast<unsigned int>(f1) |
                            static_cast<unsigned int>(f2));
}

unsigned int operator&(const flags f1, const flags f2) {
  return static_cast<unsigned int>(static_cast<unsigned int>(f1) &
                                   static_cast<unsigned int>(f2));
}

flags& operator|=(flags& f1, const flags f2) {
  f1 = f1 | f2;
  return f1;
}

/* Updates the inter-flag implications. */
void compute_multiple_flags(flags& f) {
  if (f & flags::flag4) // If f includes flag4, combine it with flag1 and flag2
    f |= (flags::flag1 | flags::flag2);
  if (f & flags::flag5) // If f includes flag5, combine it with flag3.
    f |= flags::flag3;
}

void do_complicated_stuff(flags f) {
  // update flags correctly
  compute_multiple_flags(f);

  if (f & flags::flag1)
    std::cout << "flag 1 selected\n";
  if (f & flags::flag2)
    std::cout << "flag 2 selected\n";
  if (f & flags::flag3)
    std::cout << "flag 3 selected\n";
  if (f & flags::flag4)
    std::cout << "flag 4 selected\n";
  if (f & flags::flag5)
    std::cout << "flag 5 selected\n";
}
