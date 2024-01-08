#include <iostream>
#include <cassert>

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
        sum += (current * current) % 10;
    }

    return sum % 10;
}

int fibonacci_sum_squares_fast(long long n) {
    if (n <= 1)
        return n;

    signed char previous = 0;
    signed char current  = 1;
    signed char sum      = 1;
    
    signed char peroid[20000];
    signed char current_square_peroid[20000];

    peroid[0] = 0;
    current_square_peroid[0] = 0;
    peroid[1] = 1;
    current_square_peroid[1] = 1;
    long long  i = 2;
    long long j = 0;

    for (i = 2; true; ++i) {
        signed char tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
        current_square_peroid[i] = (current * current) % 10; 
        sum += current_square_peroid[i];

        sum = sum % 10;
        peroid[i] = sum;
        
        for (j = i - 1; j >= 1; j--) {
            if (peroid[i] == peroid[j] && peroid[i-1] == peroid[j - 1]
            && current_square_peroid[i] == current_square_peroid[j] && current_square_peroid[i - 1] == current_square_peroid[j - 1]
            ) {
                goto find_period;
            }
        }
    }
    find_period:
        int p = i - j;
        int remain = i - p;
        if (n <= remain) return peroid[n];
        return peroid[(n - remain - 1) % p + remain + 1];

    return sum;
}

void test_solution() {
    assert(fibonacci_sum_squares_fast(2) == 2);
    for (int i = 3; i < 100; i++) {
        int expected = fibonacci_sum_squares_naive(i);
        int real  = fibonacci_sum_squares_fast(i);
        std::cout << "i: " << i << " expected: " << expected << " real:" << real << std::endl;
        assert(expected == real);
    }
}

int main() {
    //test_solution();
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_squares_fast(n);
}
