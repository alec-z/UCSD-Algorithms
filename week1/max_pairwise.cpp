#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
long long max_pairwise_product(vector<int> & numbers) {
    int n = numbers.size();
    int max_index0 = 0;
    for (int i = 1; i < n; i++) {
        if (numbers[i] > numbers[max_index0])
            max_index0 = i;
    }
    int max_index1 = -1;
    for (int i = 0; i < n; i++) {
        if (i != max_index0 && (max_index1 == -1 || numbers[i] > numbers[max_index1]))
            max_index1 = i;
    }
    return (long long)numbers[max_index0] * numbers[max_index1];
}

long long max_pairwise_product_brute(vector<int> & numbers) {
    int n = numbers.size();
    long long result = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j ++) {
            if ((long long)numbers[i] * numbers[j] > result) {
                result = (long long)numbers[i] * numbers[j];
            } 
        }
    }
    return result;
}


int main() {
    // {
    //     while (true) {
    //         int n = rand() % 1000 + 2;
    //         vector<int> numbers(n);
    //         cout << n << endl;
    //         for (int i = 0; i < n; i++) {
    //             numbers[i] = rand() % 10000;
    //             cout << numbers[i] << " ";
    //         }
    //         long long result0 = max_pairwise_product(numbers);
    //         long long result1 = max_pairwise_product_brute(numbers);
    //         if (result0 != result1) {
    //             cout << "result0: " << result0 << "   result1: " << result1;
    //             break;
    //         } else {
    //             cout << "OK" << endl;
    //         }
    //     }
    // }
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    std::cout << max_pairwise_product(numbers) << "\n";
    return 0;
}