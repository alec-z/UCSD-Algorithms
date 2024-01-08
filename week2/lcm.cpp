#include <iostream>
#include <cassert>

int gcd_fast(int a, int b) {
  while (b != 0) {
    int tmp = a;
    a = b;
    b = tmp % b;
  }
  return a;
}

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

long long lcm_fast(int a, int b) {
  long long gcd = gcd_fast(a, b);
  return (a / gcd) * (b / gcd) * gcd;
}

void test_solution() {
  assert(lcm_fast(2,3) == 6);
  assert(lcm_fast(6, 3) == 6);
  assert(lcm_fast(9, 12) == 36);
  for (int i = 3; i < 120; i++) {
    for (int k = 0; k < 3; k++) {
      int r = rand() % 1000000;
      long long expected = lcm_naive(i, r);
      long long real = lcm_fast(i, r);
      std::cout << "input:" << i << ":" << r << " expected:"
      << expected << " real:" << real <<std::endl;
      assert(expected == real);
    }
  }
}

int main() {
  // test_solution();
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
