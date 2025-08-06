#include <unordered_map>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
using std::vector;

unique_ptr<BinaryTreeNode<int>>
Build(const vector<int> &preorder, std::unordered_map<int, int> &node_to_in_idx,
      int pre_start, int pre_end, int in_start) {

  if (pre_start > pre_end) {
    return nullptr;
  }

  auto root_data = preorder[pre_start];
  auto root =
      unique_ptr<BinaryTreeNode<int>>(new BinaryTreeNode<int>(root_data));

  int in_root_idx = node_to_in_idx.at(root_data);

  int left_count = in_root_idx - in_start;

  root->left = Build(preorder, node_to_in_idx, pre_start + 1,
                     pre_start + left_count, in_start);

  root->right = Build(preorder, node_to_in_idx, pre_start + 1 + left_count,
                      pre_end, in_root_idx + 1);

  return root;
}

unique_ptr<BinaryTreeNode<int>>
BinaryTreeFromPreorderInorder(const vector<int> &preorder,
                              const vector<int> &inorder) {
  // TODO - you fill in here.

  if (preorder.size() == 0) {
    return nullptr;
  }

  std::unordered_map<int, int> node_to_in_idx;
  for (int i = 0; i < inorder.size(); ++i) {
    node_to_in_idx.emplace(inorder[i], i);
  }
  return Build(preorder, node_to_in_idx, 0, preorder.size() - 1, 0);
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
