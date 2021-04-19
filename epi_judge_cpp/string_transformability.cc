#include <string>
#include <unordered_set>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
using std::unordered_set;

using namespace std;



// Uses BFS to find the least steps of transformation.
int TransformString(unordered_set<string> D, const string& s, const string& t) {
  if (s.size() != t.size()) return -1;
  if (s == t) return 0;
  
  queue<string> Q;
  Q.push(s);
  D.erase(s);
  int iter_count = 1;

  while (!Q.empty()) {
    int q_sz = Q.size();
    for (int i = 0; i < q_sz; ++i) {
      string current(Q.front());
      for (int i = 0; i < current.size(); ++i) {
        for (int j = 0; j < 26; ++j) {
          string permute = current;
          permute[i] = 'a' + j;
          if (permute == t) {
            return iter_count;
          }
          if (D.find(permute) != D.end()) {
            D.erase(permute);
            Q.push(permute);
          }
        }
      }
      Q.pop();
    }
    iter_count++;
  }

  return -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"D", "s", "t"};
  return GenericTestMain(args, "string_transformability.cc",
                         "string_transformability.tsv", &TransformString,
                         DefaultComparator{}, param_names);
}
