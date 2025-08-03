#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <algorithm>

int height(const unique_ptr<BinaryTreeNode<int>> &tree) {
  if (!tree) {
    return -1;
  }

  int lh = height(tree->left) + 1;
  if (lh == -1)
    return -2;

  int rh = height(tree->right) + 1;
  if (rh == -1)
    return -2;

  if (abs(lh - rh) > 1) {
    return -2;
  }

  return std::max(lh, rh);
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>> &tree) {
  // TODO - you fill in here.
  return height(tree) != -2;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
