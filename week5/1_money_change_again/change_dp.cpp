#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cassert>

using std::vector;
using std::min;

int get_change(int m) {
  //write your code here
  vector<int> f(5, 0);
  f[0] = 0;
  for (int i = 1; i <= m; i++) {
    f[i % 5] = std::numeric_limits<int>::max();
    if (i - 4 >= 0) f[i % 5] = min(f[i % 5], f[(i - 4) % 5] + 1);
    if (i - 3 >= 0) f[i % 5] = min(f[i % 5], f[(i - 3) % 5] + 1);
    if (i - 1 >= 0) f[i % 5] = min(f[i % 5], f[(i - 1) % 5] + 1);;
  }

  return f[m % 5];
}

void test_solution() {
  //assert(get_change(1) == 1);
  int real = get_change(6);
  assert(real == 3);
}

int main() {
  //test_solution();
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
