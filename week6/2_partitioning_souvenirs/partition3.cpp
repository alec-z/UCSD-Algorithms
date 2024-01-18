#include <iostream>
#include <vector>
#include <cassert>

using std::vector;

signed char try_partition3(vector<int> &A, int i, int x, int y);

vector<vector<vector<signed char>>> f;
vector<int> sum_end_i;

int partition3(vector<int> &A) {
  //write your code here
  f.resize(A.size() + 1);
  int sum = 0;
  sum_end_i.resize(A.size() + 1);
  for (int i = 0; i <= A.size(); i++) {
    sum_end_i[i] = sum;
    if (i < A.size()) sum += A[i];
  }
  if (sum % 3 > 0) return 0;
  int part_max = sum / 3;
  for (int i = 0; i <= A.size(); i++) f[i].resize(part_max + 1);
  for (int i = 0; i <= A.size(); i++) {
    for (int j = 0; j <= part_max; j++) {
      f[i][j].resize(part_max + 1, -1);
    }
  }
  
  return try_partition3(A, A.size(), part_max, part_max);
}

signed char try_partition3(vector<int> &A, int i, int x, int y) {
  if (x < 0) return 0;
  if (y < 0) return 0;
  if (sum_end_i[i] - x - y < 0) return 0;
  if (i == 0) {
    if (x == 0 && y == 0) {
      return 1;
    } else {
      return 0;
    }
  }
  if (f[i][x][y] == -1) {
    f[i][x][y] = try_partition3(A, i - 1, x - A[i - 1], y) || try_partition3(A, i - 1, x, y - A[i - 1]) || try_partition3(A, i - 1, x, y);
  }
  return f[i][x][y];
}

void test_solution() {
  vector<int> A{3,3,3,3};
  assert(partition3(A) == 0);
  vector<int> B{1, 2, 3, 4, 5, 5, 7, 7, 8, 10, 12, 19, 25};
  assert(partition3(B) == 1);

}

int main() {
  //test_solution();
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
