#include <iostream>
#include <cassert>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
        sum += current;
        sum = sum % 10;
    }

    return sum % 10;
}




int fibonacci_sum_fast(long long n) {
    if (n <= 1)
        return n;

    signed char previous = 0;
    signed char current  = 1;
    signed char sum      = 1;
    signed char peroid[200];
    peroid[0] = 0;
    peroid[1] = 1;
    int i = 2;
    int j = 0;
    for (i = 2; true; i++) {
        signed char tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
        sum += current;
        sum = sum % 10;
        peroid[i] = sum;
        for (j = i-1; j >= 1; j--) {
            if (peroid[i] == peroid[j] && peroid[i - 1] == peroid[j - 1]) {
                goto find_period;
            }
        }
    }
    find_period:
    int p = i - j;
    int remain = i - p;
    if (n <= remain) return peroid[n];
    return peroid[(n - remain - 1) % p + remain + 1];
}

void test_solution() {
    assert(fibonacci_sum_fast(2) == 2);
    assert(fibonacci_sum_fast(3) == 4);
    assert(fibonacci_sum_fast(4) == 7);
    for (int i = 3; i < 1000; i++) {
        int real = fibonacci_sum_fast(i);
        int expected = fibonacci_sum_naive(i);
        std::cout << i << "  " << "expected: " << expected << "  real:" << real << std::endl;
        assert(real == expected);
    }
}

int main() {
    //test_solution();
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_fast(n);
}
