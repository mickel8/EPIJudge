#include <memory>
#include <stack>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::stack;
using std::unique_ptr;
using std::vector;

struct NodeStatus {
  BinaryTreeNode<int> *node;
  bool processed;
};

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>> &tree) {
  // TODO - you fill in here.
  vector<int> result;
  stack<NodeStatus> stack;

  stack.emplace(NodeStatus{tree.get(), false});

  while (!stack.empty()) {
    auto node_status = stack.top();

    stack.pop();

    if (node_status.node) {
      if (node_status.processed) {
        result.emplace_back(node_status.node->data);
      } else {
        stack.emplace(NodeStatus{node_status.node->right.get(), false});
        stack.emplace(NodeStatus{node_status.node, true});
        stack.emplace(NodeStatus{node_status.node->left.get(), false});
      }
    }
  }

  return result;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
