#include <stdexcept>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
using std::length_error;

// t [0, 1, 2, 3, 4] h
// the first to go is 4

// t [4, 3, 2, 1, 0] h
// int max = 4
// t [0, 1, 2, 3, 4] h
// 2*n -> O(n)

// t [{0, 0}, {1, 1}, {4, 4}, {3, 4}] h
// time complexity O(1)
// memory complexity O(n)
class Stack {
public:
  bool Empty() const {
    // TODO - you fill in here.
    return c.empty();
  }

  int Max() const {
    // TODO - you fill in here.
    return c.back().max;
  }

  int Pop() {
    // TODO - you fill in here.
    StackEntry e = c.back();
    c.pop_back();
    return e.value;
  }
  void Push(int x) {
    // TODO - you fill in here.
    if (Empty()) {
      c.emplace_back(x, x);
    } else {
      StackEntry last = c.back();
      int max = std::max(last.max, x);
      c.emplace_back(x, max);
    }
    return;
  }

private:
  class StackEntry {
  public:
    int value;
    int max;

    StackEntry(int value, int max) : value(value), max(max) {};
  };

  std::vector<StackEntry> c;
};
struct StackOp {
  std::string op;
  int argument;
};

namespace test_framework {
template <>
struct SerializationTrait<StackOp> : UserSerTrait<StackOp, std::string, int> {};
} // namespace test_framework

void StackTester(const std::vector<StackOp> &ops) {
  try {
    Stack s;
    for (auto &x : ops) {
      if (x.op == "Stack") {
        continue;
      } else if (x.op == "push") {
        s.Push(x.argument);
      } else if (x.op == "pop") {
        int result = s.Pop();
        if (result != x.argument) {
          throw TestFailure("Pop: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "max") {
        int result = s.Max();
        if (result != x.argument) {
          throw TestFailure("Max: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "empty") {
        int result = s.Empty();
        if (result != x.argument) {
          throw TestFailure("Empty: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else {
        throw std::runtime_error("Unsupported stack operation: " + x.op);
      }
    }
  } catch (length_error &) {
    throw TestFailure("Unexpected length_error exception");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "stack_with_max.cc", "stack_with_max.tsv",
                         &StackTester, DefaultComparator{}, param_names);
}
