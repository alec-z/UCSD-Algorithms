#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>

using std::vector;
using std::swap;

int try_majority_element(vector<int> &a, int left, int right, int threhold) {
  int len = right - left + 1;
  swap(a[left], a[left + (rand() % len)]);
  int v= a[left];
  int lt = left;
  int gt = right;
  int i = left;
  
  while (i <= gt) {
    if (a[i] < v) swap(a[lt++], a[i++]);
    else if (a[i] > v) swap(a[gt--], a[i]);
    else i++;

  }
  if (i - lt > threhold) return a[i - 1];
  else if (lt - left > threhold) return  try_majority_element(a, left, lt - 1, threhold);
  else if (right - gt > threhold) return try_majority_element(a, gt + 1, right, threhold);
  else return -1;
}

int get_majority_element(vector<int> &a, int left, int right) {
  if (left > right) return -1;
  if (left == right) return a[left];
  //write your code here
  //todo :random
  
  return try_majority_element(a, left, right, (right - left + 1) / 2);
}

int get_majority_element_native(vector<int> &a, int left, int right) {
  int threhold = (right - left + 1) / 2;
  sort(a.begin(),a.end());
  for (int i = 0; i < a.size(); ) {
    int j = i + 1;
    for (; a[j] == a[i]; j++) {}
    if (j - i > threhold) {return a[i];}
    i = j; 
  }
  return -1;

}

void test_solution() {
  vector<int> a{2, 3, 9, 2, 2};
  vector<int> b = a;
  int expected = get_majority_element_native(a, 0, a.size() - 1);
  int real = get_majority_element(b, 0, b.size()-1);
  assert(real == expected);
  for (int n = 1; n < 9; n++) {
    int v = rand() % 10;
    for (int repeat = 1; repeat <n; repeat++) {
      a.clear();
      b.clear();
      for (int k = 0; k < repeat; k++) {
        a.push_back(v);
      }
      for (int k = 0; k < n -repeat; k++) {
        a.push_back(rand() % 10);
      }
      b = a;
      int expected = get_majority_element_native(a, 0, a.size() - 1);
      int real = get_majority_element(a, 0, a.size()-1);
      assert(real == expected);

    }

  }

}

int main() {
  //test_solution();
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size() - 1) != -1) << '\n';
}
