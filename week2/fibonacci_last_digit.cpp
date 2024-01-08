#include <iostream>
#include <cassert>

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
    }

    return current % 10;
}

int get_fibonacci_last_digit_fast(int n) {
    int result[60] = {0,  1,  1,  2,  3,  5,  8,  3,  1,  4,  5,  9,  4,  3,  7,  0,  7,  7,  4,  1,  5,  6,  1,  7,  8,  5,  3,  8,  1,  9,  0,  9,  9,  8,  7,  5,  2,  7,  9,  6,  5,  1,  6,  7,  3,  0,  3,  3,  6,  9,  5,  4,  9,  3,  2,  5,  7,  2,  9,  1};
    return result[n % 60];
}
void test_solution() {
    assert(get_fibonacci_last_digit_fast(3) == 2);
    assert(get_fibonacci_last_digit_fast(0) == 0);
    assert(get_fibonacci_last_digit_fast(1) == 1);
    for (int i = 0; i < 140; i ++) {
        int expected = get_fibonacci_last_digit_naive(i);
        int fast = get_fibonacci_last_digit_fast(i);
        std::cout << "n:" << i << "  fast:" << fast << "  " << "expected: " << expected << std::endl;
        assert(get_fibonacci_last_digit_fast(i) == get_fibonacci_last_digit_naive(i));
    }
}
int main() {
    int n;
    std::cin >> n;
    int c = get_fibonacci_last_digit_fast(n);
    std::cout << c << '\n';
    //test_solution();
    }
