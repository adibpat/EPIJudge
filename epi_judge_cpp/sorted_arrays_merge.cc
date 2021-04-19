#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
using std::vector;

using namespace std;

struct Elem {
  pair<const int*, const int*> p;
  Elem(const int *a, const int *b) : p(make_pair(a, b)) {}
  bool operator<(const Elem& that) const {
    return *(p.first) > *(that.p.first);
  }
};

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {

  priority_queue<Elem, vector<Elem > > Q;

  for (auto& arr : sorted_arrays) {
    if (arr.size()) Q.push(Elem(&arr[0], &arr[arr.size()-1]));
  }

  vector<int> result;

  while (!Q.empty()) {
    Elem current(Q.top()); Q.pop();
    result.push_back(*(current.p.first));
    current.p.first++;
    if (current.p.first <= current.p.second) {
      Q.push(current);
    }
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
