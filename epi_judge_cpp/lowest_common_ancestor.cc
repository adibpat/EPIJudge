#include <memory>
#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

bool searchNode(const unique_ptr<BinaryTreeNode<int>>& tree, 
                const unique_ptr<BinaryTreeNode<int>>& node) 
{
  if (!tree) return false;
  if (tree == node) return true;

  return searchNode(tree->left, node) || searchNode(tree->right, node);
}

std::pair<bool, BinaryTreeNode<int>* > findLCA(const unique_ptr<BinaryTreeNode<int>>& tree,
                                             const unique_ptr<BinaryTreeNode<int>>& node0,
                                             const unique_ptr<BinaryTreeNode<int>>& node1)
{
  if (!tree) return std::make_pair(false, nullptr);

  if (tree == node0 || tree == node1) {
    if (searchNode(tree, node0) && searchNode(tree, node1)) return std::make_pair(true, tree.get());
  }

  if (searchNode(tree->left, node0) && searchNode(tree->right, node1)) return std::make_pair(true, tree.get());
  if (searchNode(tree->right, node0) && searchNode(tree->left, node1)) return std::make_pair(true, tree.get());

  std::pair<bool, BinaryTreeNode<int>* > rc1 = findLCA(tree->left, node0, node1);
  std::pair<bool, BinaryTreeNode<int>* > rc2 = findLCA(tree->right, node0, node1);

  if (rc1.first) return std::make_pair(true, rc1.second);

  if (rc2.first) return std::make_pair(true, rc2.second);

  return std::make_pair(false, nullptr);
}

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& tree,
                         const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  // TODO - you fill in here.
  return findLCA(tree, node0, node1).second;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return LCA(tree, node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
