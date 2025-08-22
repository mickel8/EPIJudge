#include <deque>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::vector;
using std::queue;
using std::pair;
void FlipColor(int x, int y, vector<deque<bool>>* image_ptr) {
  // TODO - you fill in here.

  queue<pair<int, int>> q;
  q.emplace(x, y);

  auto &image = *image_ptr;
  bool color = image[x][y];

  while (!q.empty()) {
    auto p = q.front();
    q.pop();

    if (p.first >= 0 && p.first < image.size() && p.second >= 0 && p.second < image[p.first].size()) {
      if (image[p.first][p.second] == color) {
        image[p.first][p.second] = !color;
        
        for (pair<int, int> n : std::initializer_list<pair<int, int>>{{p.first, p.second-1}, {p.first, p.second+1}, {p.first-1, p.second}, {p.first+1, p.second}}){
          q.push(n);
        }
      }
    }
  }

  return;
}
vector<vector<int>> FlipColorWrapper(TimedExecutor& executor, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int>& row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&] { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}
