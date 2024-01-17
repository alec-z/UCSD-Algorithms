#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using std::vector;
using std::max;

int lcs2(vector<int> &a, vector<int> &b) {
  //write your code here
  vector<vector<int>> f(2);
  f[0].resize(b.size() + 1);
  f[1].resize(b.size() + 1);
  for (int i = 1; i <= a.size(); i++) {
    for (int j = 1; j <= b.size(); j++) {
      int &cur = f[i % 2][j];
      cur = f[(i - 1) % 2][j - 1];
      if (a[i - 1] == b[j - 1]) cur = max(cur, f[(i - 1) % 2][j - 1] + 1);
      cur = max(cur, f[(i - 1) % 2][j]);
      cur = max(cur, f[i % 2][j - 1]);
    }
  }
  return f[a.size() % 2][b.size()];
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
