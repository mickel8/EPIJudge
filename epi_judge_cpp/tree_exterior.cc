#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;

void LeftExterior(const std::unique_ptr<BinaryTreeNode<int>> &tree,
                  vector<const unique_ptr<BinaryTreeNode<int>> *> &exterior,
                  bool &left_path_finished) {

  if (tree == nullptr) {
    return;
  }

  if (tree->left == nullptr && tree->right == nullptr) {
    left_path_finished = true;
    exterior.emplace_back(&tree);
  } else if (!left_path_finished) {
    exterior.emplace_back(&tree);
  }

  LeftExterior(tree->left, exterior, left_path_finished);
  LeftExterior(tree->right, exterior, left_path_finished);
}

void RightExterior(const std::unique_ptr<BinaryTreeNode<int>> &tree,
                   vector<const unique_ptr<BinaryTreeNode<int>> *> &exterior,
                   bool &right_path_finished) {

  if (tree == nullptr) {
    return;
  }

  if (tree->left == nullptr && tree->right == nullptr) {
    right_path_finished = true;
    exterior.emplace_back(&tree);
  } else if (!right_path_finished) {
    exterior.emplace_back(&tree);
  }

  RightExterior(tree->right, exterior, right_path_finished);
  RightExterior(tree->left, exterior, right_path_finished);
}

vector<const unique_ptr<BinaryTreeNode<int>> *>
ExteriorBinaryTree(const unique_ptr<BinaryTreeNode<int>> &tree) {
  // TODO - you fill in here.

  if (tree == nullptr) {
    return vector<const unique_ptr<BinaryTreeNode<int>> *>();
  }

  vector<const unique_ptr<BinaryTreeNode<int>> *> left_exterior;
  vector<const unique_ptr<BinaryTreeNode<int>> *> right_exterior;
  bool left_path_finished = false;
  bool right_path_finished = false;

  left_exterior.emplace_back(&tree);
  LeftExterior(tree->left, left_exterior, left_path_finished);
  RightExterior(tree->right, right_exterior, right_path_finished);

  for (int i = right_exterior.size() - 1; i >= 0; --i) {
    left_exterior.emplace_back(right_exterior[i]);
  }

  return left_exterior;
}
vector<int>
CreateOutputVector(const vector<const unique_ptr<BinaryTreeNode<int>> *> &L) {
  if (std::find(std::begin(L), std::end(L), nullptr) != std::end(L)) {
    throw TestFailure("Resulting list contains nullptr");
  }
  std::vector<int> output;
  for (const auto *l : L) {
    output.push_back((*l)->data);
  }
  return output;
}

vector<int>
ExteriorBinaryTreeWrapper(TimedExecutor &executor,
                          const unique_ptr<BinaryTreeNode<int>> &tree) {
  auto result = executor.Run([&] { return ExteriorBinaryTree(tree); });

  return CreateOutputVector(result);
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(args, "tree_exterior.cc", "tree_exterior.tsv",
                         &ExteriorBinaryTreeWrapper, DefaultComparator{},
                         param_names);
}
