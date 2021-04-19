#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool checkSymmetry(const unique_ptr<BinaryTreeNode<int>>& root1, 
                   const unique_ptr<BinaryTreeNode<int>>& root2) {
    if (!root1 && !root2) 
      return true;
    
    if (root1 && root2) {
      return root1->data == root2->data &&
             checkSymmetry(root1->left, root2->right) &&
             checkSymmetry(root1->right, root2->left);
    }

    return false;
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  
  return tree == nullptr || checkSymmetry(tree->left, tree->right);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
