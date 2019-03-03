#include "test_framework/generic_test.h"
unsigned long long ReverseBits(unsigned long long x) {
  for (int i = 0, j = 63; i < j; ++i, --j) {
    if ((((x >> i) & 1)) != ((x >> j) & 1)) {
      x ^= ((1L << i) | (1L << j));
    }
  }
  return x;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
