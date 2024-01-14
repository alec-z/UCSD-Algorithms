#include <iostream>
#include <vector>
#include <cassert>

using std::vector;

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
  long long number_of_inversions = 0;
  if (right <= left + 1) return number_of_inversions;
  size_t ave = left + (right - left) / 2;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  number_of_inversions += get_number_of_inversions(a, b, ave, right);
  //write your code here
  int i = left;
  int j = ave;
  
  for (int k = left; k < right; k++) {
    if (i == ave) {b[k] = a[j++];}
    else if (j == right) {b[k] = a[i++];}
    else if (a[i] <= a[j]) { b[k] = a[i++];}
    else {
      b[k] = a[j++];
      number_of_inversions += (ave - i);
    }
  }
  for (int k = left; k < right; k++) {
    a[k] = b[k];
  }
  return number_of_inversions;
}

void test_solution() {
  vector<int> a {1, 3, 2, 0};
  vector<int> b(a.size());
  assert(get_number_of_inversions(a, b, 0, a.size()) == 4);
}

int main() {
  test_solution();

  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size());
  std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
