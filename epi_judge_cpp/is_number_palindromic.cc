#include "test_framework/generic_test.h"
bool IsPalindromeNumber(int x) {
  /* O(n) solution
  if (x < 0) return (false);
  int comp = 0; int temp = x;
  while (temp) {
    comp = comp*10 + (temp%10);
    temp /= 10;
  }
  return (x == comp);
  */

  /* Optimized O(n) solution */
  if (x < 0) return (false);
  int num_of_digits = static_cast<int> (floor(log10(x))) + 1; // log10(1) = 0, log10(10) = 1, log10(100) = 2,..so # of digits is log10(x) + 1
  int most_sig_power = static_cast<int> (pow(10, num_of_digits -1));
  int remaining_digits = x;
  for (int i = 0; i < num_of_digits/2; ++i) {
    if (x/most_sig_power != remaining_digits%10) return (false);
    remaining_digits /= 10;
    x %= most_sig_power;
    most_sig_power /= 10;
  }
  return (true);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
