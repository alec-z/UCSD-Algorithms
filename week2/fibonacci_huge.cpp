#include <iostream>
#include <cassert>

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % m;
    }

    return current % m;
}
long long get_fibonacci_huge_fast(long long n, long long m) {
    if (n <= 1)
        return n;
    if (n < m * m || m > 10000) {
        return get_fibonacci_huge_naive(n, m);
    }

    int previous = 0;
    int current  = 1;

    int peroid[m * m * 2];
    peroid[0] = 0;
    peroid[1] = 1;
    int i = 1;
    int j = 0;
    for (i = 2; true; i++) {
        int tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % m;
        peroid[i] = current;
        for (j = i - 1; j >= 1; j--) {
            if (peroid[i] == peroid[j] && peroid[i - 1] == peroid[j - 1]) {
                goto find_period;
            }
        }
    }
    find_period:
    int p = i - j;
    int remain = i - p;
    if (n <= remain) {
        return peroid[n];
    } else {
        int pos = (n - remain - 1) % p;
        return peroid[remain + 1 + pos];
    }
}

void test_solution() {
    assert(get_fibonacci_huge_fast(6, 2) == 0);
    assert(get_fibonacci_huge_fast(5, 2) == 1);
    for (int i = 10; i < 10000; i++) {
        for (int j = 2; j < 6; j++) {
            int expected = get_fibonacci_huge_naive(i, j);
            int real = get_fibonacci_huge_fast(i, j);
            std::cout << "input:" << i  << " " << j << " expected: " << expected << "  real: " << real << std::endl;
            assert(expected == real);  
        }
    }
}

int main() {
    long long n, m;
    test_solution();
    std::cin >> n >> m;
    //n = 9999999, m = 2;
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
