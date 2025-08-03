#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool IsSymmetricPair(const unique_ptr<BinaryTreeNode<int>> &t1,
                     const unique_ptr<BinaryTreeNode<int>> &t2) {
  if (t1 == nullptr && t2 == nullptr) {
    return true;
  }

  if (t1 == nullptr || t2 == nullptr) {
    return false;
  }

  return t1->data == t2->data && IsSymmetricPair(t1->left, t2->right) &&
         IsSymmetricPair(t1->right, t2->left);
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>> &tree) {
  // TODO - you fill in here.
  return tree == nullptr || IsSymmetricPair(tree->left, tree->right);
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
