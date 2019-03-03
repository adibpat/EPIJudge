#include "test_framework/generic_test.h"
short Parity(unsigned long long x) {
  int shift = 32;
  while (shift) {
    x ^= x >> shift;
    shift = shift >> 1;
  }
  x &= 1;
  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
