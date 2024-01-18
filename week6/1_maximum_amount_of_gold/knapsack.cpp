#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


using std::vector;
using std::max;

int optimal_weight(int W, const vector<int> &w) {
  int max_w = 0;
  for (int i = 0; i < w.size(); i++) {max_w = max(max_w, w[i]); }
  int i_len = max_w + 1;
  vector<vector<int>> f(i_len);
  for (int i = 0; i < i_len; i ++) f[i].resize(w.size() +1);
  for (int i = 1; i <= W; i++) {
    int cur_i = i % i_len;
    for (int j = 1; j <= w.size(); j++) {
      f[cur_i][j] = f[cur_i][j - 1];
      if (i >= w[j - 1]) {f[cur_i][j] = max(f[cur_i][j], f[(i - w[j - 1]) % i_len][j - 1] + w[j - 1]);} 
    }  
  }
  return f[W % i_len][w.size()];
}

void test_solution() {
  int W = 10;
  vector<int> w {1, 4, 8};
  assert(optimal_weight(W, w) == 9);
}

int main() {
  //test_solution();
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
