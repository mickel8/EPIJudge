#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

int Sum(const unique_ptr<BinaryTreeNode<int>> &tree, int partial_sum) {
  if (tree == nullptr) {
    return 0;
  }

  partial_sum = 2 * partial_sum + tree->data;

  if (tree->left == nullptr && tree->right == nullptr) {
    return partial_sum;
  }

  return Sum(tree->left, partial_sum) + Sum(tree->right, partial_sum);
}

int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>> &tree) {
  // TODO - you fill in here.
  return Sum(tree, 0);
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "sum_root_to_leaf.cc", "sum_root_to_leaf.tsv",
                         &SumRootToLeaf, DefaultComparator{}, param_names);
}
