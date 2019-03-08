#include <string>
#include "test_framework/generic_test.h"
using std::string;

string ConvertBase(const string& num_as_string, int b1, int b2) {
  unsigned long long x = 0;

  for (size_t i = (num_as_string.front() == '-' ? 1:0); i < num_as_string.size(); i++) {
    x = x*b1;
    if (std::isdigit(num_as_string[i])) {
      x += num_as_string[i] - '0';
    } else {
      x += num_as_string[i] - 'A' + 10;
    }
  }
  if (x == 0) {
    return num_as_string.front() == '-'? "-0" : "0";
  }
  string result;
  while (x) {
    if (x%b2 < 10) { 
      result.push_back(x%b2 + '0');
    } else {
      result.push_back(x%b2 - 10 + 'A');
    }
    x /= b2;
  };

  if (num_as_string.front() == '-') result.push_back('-');
  std::reverse(result.begin(), result.end());
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
