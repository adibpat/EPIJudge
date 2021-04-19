#include <string>
#include <vector>
#include <memory>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

unique_ptr<BinaryTreeNode<int> > ReconstructPreorderHelper(const vector<int*>& preorder, int& pos)
{
  if (pos >= preorder.size()) return nullptr;

  if (preorder[pos] == nullptr) return nullptr;
  
  unique_ptr<BinaryTreeNode<int> > node = std::make_unique<BinaryTreeNode<int> >(*(preorder[pos]));
  pos++;
  node->left = ReconstructPreorderHelper(preorder, pos);
  pos++;
  node->right = ReconstructPreorderHelper(preorder, pos);

  return node;
}

unique_ptr<BinaryTreeNode<int> > ReconstructPreorder(
    const vector<int*>& preorder) {
  // TODO - you fill in here.
  int pos = 0;
  return ReconstructPreorderHelper(preorder, pos);
}
unique_ptr<BinaryTreeNode<int>> ReconstructPreorderWrapper(
    TimedExecutor& executor, const vector<string>& preorder) {
  vector<int> values;
  vector<int*> ptrs;
  values.reserve(preorder.size());
  for (auto& s : preorder) {
    if (s == "null") {
      ptrs.push_back(nullptr);
    } else {
      int i = std::stoi(s);
      values.push_back(i);
      ptrs.push_back(&values.back());
    }
  }

  return executor.Run([&] { return ReconstructPreorder(ptrs); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "preorder"};
  return GenericTestMain(args, "tree_from_preorder_with_null.cc",
                         "tree_from_preorder_with_null.tsv",
                         &ReconstructPreorderWrapper, DefaultComparator{},
                         param_names);
}
