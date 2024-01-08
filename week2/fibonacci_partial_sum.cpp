#include <iostream>
#include <vector>
#include <cassert>
using std::vector;


long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current % 10;
    }

    return sum % 10;
}

int get_fibonacci_last_digit_fast(long long n) {
    int result[60] = {0,  1,  1,  2,  3,  5,  8,  3,  1,  4,  5,  9,  4,  3,  7,  0,  7,  7,  4,  1,  5,  6,  1,  7,  8,  5,  3,  8,  1,  9,  0,  9,  9,  8,  7,  5,  2,  7,  9,  6,  5,  1,  6,  7,  3,  0,  3,  3,  6,  9,  5,  4,  9,  3,  2,  5,  7,  2,  9,  1};
    return result[n % 60];
}

int get_fibonacci_partial_sum_fast(long long from, long long to) {
    

    signed char previous = get_fibonacci_last_digit_fast(from);
    signed char current  = get_fibonacci_last_digit_fast(from + 1);
    signed char sum      = (previous + current) % 10;
    signed char peroid[20000];
    signed char current_fib_peroid[20000];
    peroid[0] = previous;
    current_fib_peroid[0] = previous;
    peroid[1] = sum;
    current_fib_peroid[1] = current;
    int i = 0;
    int j = 0;
    for (i = 2; true; i++) {
        signed char tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
        sum += current;
        sum = sum % 10;
        peroid[i] = sum;
        current_fib_peroid[i] = current % 10;
        for (j = i-1; j >= 1; j--) {
            if (peroid[i] == peroid[j] && peroid[i - 1] == peroid[j - 1] 
            && current_fib_peroid[i] == current_fib_peroid[j] && current_fib_peroid[i - 1] == current_fib_peroid[j - 1]) {
                goto find_period;
            }
        }
    }
    find_period:
    int p = i - j;
    int remain = i - p;
    long long n = to - from;
    if (n <= remain) return peroid[n];
    return peroid[(n - remain - 1) % p + remain + 1];
}

void test_solution() {
    //assert(get_fibonacci_partial_sum_fast(2, 3) == 3);
    //assert(get_fibonacci_partial_sum_fast(2, 4) == 6);
    assert(get_fibonacci_partial_sum_fast(567717153638, 567717153638) == 9);
    for (int i = 4; i < 100; i++) {
        int real = get_fibonacci_partial_sum_fast(i / 2, i);
        int expected = get_fibonacci_partial_sum_naive(i / 2, i);
        std::cout << i / 2 << " to: "  << i << "   expected: " << expected << "  real:" << real << std::endl;
        assert(real == expected);
    }
}



int main() {
    //test_solution();
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
