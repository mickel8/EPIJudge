#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

int depth(const BinaryTreeNode<int> *node) {
  int depth = 0;
  while (node->parent) {
    ++depth;
    node = node->parent;
  }
  return depth;
}

BinaryTreeNode<int> *Lca(const unique_ptr<BinaryTreeNode<int>> &node0,
                         const unique_ptr<BinaryTreeNode<int>> &node1) {
  // TODO - you fill in here.
  int n0h = depth(node0.get());
  int n1h = depth(node1.get());

  BinaryTreeNode<int> *n0i = node0.get();
  BinaryTreeNode<int> *n1i = node1.get();

  while (n0h > n1h) {
    n0i = n0i->parent;
    n0h--;
  }

  while (n1h > n0h) {
    n1i = n1i->parent;
    n1h--;
  }

  while (n0i != n1i) {
    n0i = n0i->parent;
    n1i = n1i->parent;
  }

  return n0i;
}
int LcaWrapper(TimedExecutor &executor,
               const unique_ptr<BinaryTreeNode<int>> &tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>> &node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>> &node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
