#include "test_framework/generic_test.h"

unsigned long long AddWoUsingAdd(unsigned long long val1, unsigned long long val2) {
  //std::cout << "Adding " << val1 << " and " << val2 << std::endl;
  unsigned long long result = 0, carry = 0;
  int i = 0;
  while(val1 || val2) {
    result = result | (((val1 & 1) ^ (val2 & 1) ^ carry) << i);
    if ((val1 & 1) ^ (val2 & 1)) {
      carry = (carry & 1);
    } else {
      carry = (val1 & 1);
    }
    val1 = val1 >> 1; val2 = val2 >> 1;
    i++;
  }
  //std::cout << "Result is " << (result | (carry << i)) << std::endl;
  return (result | (carry << i));
}

unsigned long long Multiply(unsigned long long x, unsigned long long y) {
  int i = 0; 
  unsigned long long result = 0;
  while (y) {
    if ((1L << i) & y) {
      result = AddWoUsingAdd(result, x << i);
      y = y & (y-1);
    }
    i++;
  }
  return (result);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_multiply.cc",
                         "primitive_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
