#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using std::vector;

vector<int> optimal_sequence(int n) {
  std::vector<int> reconstruction(n + 1, -1);
  std::vector<int> f(n + 1, std::numeric_limits<int>::max());
  std::vector<int> sequence;
  f[1] = 0;
  reconstruction[1] = 0;
  for (int i = 2; i <= n; i++) {
    if (i % 3 == 0 && i / 3 >= 1 && f[i / 3] + 1 < f[i]) {
      f[i] = f[i / 3] + 1;
      reconstruction[i] = i / 3;
    }
    if (i % 2 == 0 && i / 2 >= 1 && f[i / 2] + 1 < f[i]) {
      f[i] = f[i / 2] + 1;
      reconstruction[i] = i / 2;
    }
    if (i - 1 >= 1 && f[i - 1] + 1 < f[i]) {
      f[i] = f[i - 1] + 1;
      reconstruction[i] = i - 1;
    }
  }
  int len=0;
  int p = n;
  while (p > 0) {
    sequence.push_back(p);
    p = reconstruction[p];
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
