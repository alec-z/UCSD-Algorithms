#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::max;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
  //write your code here
  vector<vector<vector<int>>> f(2);
  f[0].resize(b.size() + 1);
  f[1].resize(b.size() + 1);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j <= b.size(); j++) {
      f[i][j].resize(c.size() + 1);
    }
  }

  for (int i = 1; i <= a.size(); i ++) {
    for (int j = 1; j <= b.size(); j ++) {
      for (int k = 1; k <= c.size(); k++) {
        int ci = i % 2;
        int pi = (i - 1) % 2;
        f[ci][j][k] = f[pi][j - 1][k -1];
        if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1]) f[ci][j][k] = max(f[ci][j][k], f[pi][j - 1][k - 1] + 1);
        f[ci][j][k] = max(f[ci][j][k], f[pi][j][k]);
        f[ci][j][k] = max(f[ci][j][k], f[ci][j - 1][k]);
        f[ci][j][k] = max(f[ci][j][k], f[ci][j][k - 1]);
      }
    }
  }
  return f[a.size() % 2][b.size()][c.size()];
}

int main() {
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
