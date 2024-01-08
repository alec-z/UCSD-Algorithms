#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using std::vector;
using std::string;

bool less(string x, string y) {
  int lx = x.size();
  int ly = y.size();
  int l = std::min(lx,  ly);
  for (int i=0; i < l; i++) {
    if (x[i] != y[i]) {
      return x[i] > y[i];
    }
  }
  if (lx < ly) {
    return less(y, y.substr(l, ly - l) + y.substr(0, l));
  } else if (lx > ly) {
    return less(x.substr(l, lx-l) + x.substr(0, l), x);
  } else {
    return false;
  }
}
void test_solution() {
  assert(less(string("123"), string("1")) == true);
}

string largest_number(vector<string> a) {
  //write your code here
  std::stringstream ret;
  std::sort(a.begin(), a.end(), less);
  for (size_t i = 0; i < a.size(); i++) {
    ret << a[i];
  }
  string result;
  ret >> result;
  return result;
}

int main() {
  //test_solution();
  int n;
  std::cin >> n;
  vector<string> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << largest_number(a);
}
