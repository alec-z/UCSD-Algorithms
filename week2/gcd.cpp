#include <iostream>
#include <cassert>
#include <cstdlib>

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_fast(int a, int b) {
  while (b != 0) {
    int tmp = a;
    a = b;
    b = tmp % b;
  }
  return a;
}
void test_solution() {
  assert(gcd_fast(3, 0) == 3);
  assert(gcd_fast(0, 3) == 3);
  assert(gcd_fast(2, 4) == 2);
  assert(gcd_fast(9, 6) == 3);
  assert(gcd_fast(3, 1) == 1);
  for (int i = 2; i < 100; i++) {
    for (int k = 0; k < 3; k++) {
      int r = rand() % 100 + 2;
      int expected = gcd_naive(i, r);
      int real = gcd_fast(i, r);
      std::cout << "input:" << i << ", " << r << "  " << "expected:" << expected << "  real:" << real << std::endl;
      assert(gcd_naive(i, r) == gcd_fast(i, r));
    }
  }
}

int main() {
  // test_solution();
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd_fast(a, b) << std::endl;
  return 0;
}
