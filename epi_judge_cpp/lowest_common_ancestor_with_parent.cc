#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

bool isParent(BinaryTreeNode<int>* parent, 
              BinaryTreeNode<int>* child) {
  if (!parent || !child) return false;
  
  if (child == parent) return true;

  BinaryTreeNode<int>* current = child;
  while (current->parent) {
    if (current->parent == parent) return true;
    current = current->parent;
  }

  return false;
}

BinaryTreeNode<int>* LCAHelper(BinaryTreeNode<int>* node0,
                               BinaryTreeNode<int>* node1) {
  if (!node0 || !node1) return node0 ? node0 : node1 ? node1 : nullptr;
  
  if (isParent(node0, node1)) return node0;
  if (isParent(node1, node0)) return node1;

  auto ptr1 = LCAHelper(node0->parent, node1);
  if (ptr1) return ptr1;

  auto ptr2 = LCAHelper(node1->parent, node0);
  if (ptr2) return ptr2;

  return nullptr;
}

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  return LCAHelper(node0.get(), node1.get());
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return LCA(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
