#include <memory>
#include <vector>
#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void FindKLargestInBSTHelper(BstNode<int>* tree, vector<int>&result, int k) {
  if (tree == nullptr) return;

  if (k == result.size()) return;
  FindKLargestInBSTHelper(tree->right.get(), result, k);
  if (k == result.size()) return;
  result.push_back(tree->data);
  FindKLargestInBSTHelper(tree->left.get(), result, k);
}

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
  vector<int> result;

  FindKLargestInBSTHelper(tree.get(), result, k);

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         &UnorderedComparator<std::vector<int>>, param_names);
}
