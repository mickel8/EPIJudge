#include <cstddef>
#include <vector>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>> &tree) {
  // TODO - you fill in here.

  bool right_processed = false;
  bool left_processed = false;

  vector<int> result;

  auto iter = tree.get();

  while (iter != nullptr) {

    if (left_processed) {
      result.emplace_back(iter->data);

      if (iter->right == nullptr) {
        left_processed = false;
        if (iter->parent && iter == iter->parent->left.get()) {
          left_processed = true;
        } else {
          right_processed = true;
        }

        iter = iter->parent;
      } else {
        left_processed = false;
        iter = iter->right.get();
      }
    } else if (right_processed) {
      right_processed = false;
      if (iter->parent && iter == iter->parent->left.get()) {
        left_processed = true;
      } else {
        right_processed = true;
      }

      iter = iter->parent;
    } else if (iter->left == nullptr) {
      if (iter->right == nullptr) {
        result.emplace_back(iter->data);

        if (iter->parent && iter == iter->parent->left.get()) {
          left_processed = true;
        } else {
          right_processed = true;
        }

        iter = iter->parent;
      } else {
        left_processed = true;
      }
    } else {
      iter = iter->left.get();
    }
  }

  return result;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
