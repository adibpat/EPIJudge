#include "test_framework/generic_test.h"
bool IsPalindromeNumber(int x) {
  if (x < 0) return (false);
  int comp = 0; int temp = x;
  while (temp) {
    comp = comp*10 + (temp%10);
    temp /= 10;
  }
  return (x == comp);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
