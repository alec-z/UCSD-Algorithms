#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <cassert>

using std::string;
using std::vector;
using std::min;

int edit_distance(const string &str1, const string &str2) {
  vector<vector<int>> f(2);
  f[0].resize(str2.size() + 1);
  f[1].resize(str2.size() + 1);
  for (int j = 0; j <= str2.size(); j++) f[0][j] = j;
  for (int i = 1; i <= str1.size(); i++) {
    f[i % 2][0] = i;
    for (int j = 1; j <= str2.size(); j++) {
      f[i % 2][j] = std::numeric_limits<int>::max();
      f[i % 2][j] = min(f[i % 2][j], f[(i - 1) % 2][j] + 1);
      f[i % 2][j] = min(f[i % 2][j], f[i % 2][j - 1] + 1);
      if (str1[i - 1] == str2[j - 1]) f[i % 2][j] = min(f[i % 2][j], f[(i - 1) % 2][j - 1]);
      else f[i % 2][j] = min(f[i % 2][j], f[(i - 1) % 2][j - 1] + 1);
    }
  }
  return f[str1.size() % 2][str2.size()];
}
void test_solution() {
  int real = edit_distance(string("sh"), string("p"));
  assert(real == 3);
}

int main() {
  //test_solution();
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
