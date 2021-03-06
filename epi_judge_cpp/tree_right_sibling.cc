#include <memory>
#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;
template <typename T>
struct BinaryTreeNode {
  T data;
  unique_ptr<BinaryTreeNode<T>> left, right;
  BinaryTreeNode<T>* next = nullptr;  // Populates this field.

  explicit BinaryTreeNode(T data) : data(data){};
};

std::queue<BinaryTreeNode<int>* > Q;

void ConstructRightSibling(BinaryTreeNode<int>* tree) {
  if (tree) Q.push(tree);

  while (!Q.empty()) {
    int q_sz = Q.size();
    for (int i = 0; i < q_sz; ++i) {
      BinaryTreeNode<int>* front = Q.front(); Q.pop();
      if (front->left) Q.push(front->left.get());
      if (front->right) Q.push(front->right.get());
      if (i < q_sz - 1 && Q.front()) front->next = Q.front();
    }
  }
 
  return;
}
template <>
struct SerializationTraits<unique_ptr<BinaryTreeNode<int>>>
    : BinaryTreeSerializationTraits<unique_ptr<BinaryTreeNode<int>>, false> {};

std::vector<std::vector<int>> ConstructRightSiblingWrapper(
    TimedExecutor& executor, unique_ptr<BinaryTreeNode<int>>& tree) {
  executor.Run([&] { ConstructRightSibling(tree.get()); });

  std::vector<std::vector<int>> result;
  auto level_start = tree.get();
  while (level_start) {
    result.emplace_back();
    auto level_iter = level_start;
    while (level_iter) {
      result.back().push_back(level_iter->data);
      level_iter = level_iter->next;
    }
    level_start = level_start->left.get();
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(
      args, "tree_right_sibling.cc", "tree_right_sibling.tsv",
      &ConstructRightSiblingWrapper, DefaultComparator{}, param_names);
}
