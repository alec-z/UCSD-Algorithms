#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <regex>
#include <limits>
#include <cassert>

using std::vector;
using std::string;
using std::max;
using std::min;

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}




long long get_maximum_value(const string &exp) {
  //write your code here
  vector<vector<long long>> min_f;
  vector<vector<long long>> max_f;
  vector<long long> nums;
  vector<char> ops;
  std::regex rgx("\\d+");
  std::sregex_token_iterator iter(exp.begin(),
    exp.end(),
    rgx);
  std::sregex_token_iterator end;
  for ( ; iter != end; ++iter) nums.push_back(std::stoll(*iter));
  for (int i = 0; i < exp.size(); i++) if (exp[i] =='*' ||  exp[i] =='+' || exp[i] =='-') ops.push_back(exp[i]);
  int nums_size = nums.size();
  max_f.resize(nums_size);
  min_f.resize(nums_size);
  for (int i = 0; i < nums_size; i++) {
    max_f[i].resize(nums_size, std::numeric_limits<long long>::min());
    min_f[i].resize(nums_size, std::numeric_limits<long long>::max());
  }
  for (int i = 0; i < nums_size; i++) {
    max_f[i][i] = nums[i];
    min_f[i][i] = nums[i];
  }
  for (int l = 2; l <= nums_size; l++) {
    for (int i = 0; i <= nums_size - l; i++) {
      int j = i + l - 1;
      for (int k = i; k <= j - 1; k++) {
        long long a = eval(max_f[i][k], max_f[k + 1][j], ops[k]);
        long long b = eval(max_f[i][k], min_f[k + 1][j], ops[k]);
        long long c = eval(min_f[i][k], max_f[k + 1][j], ops[k]);
        long long d = eval(min_f[i][k], min_f[k + 1][j], ops[k]);
        max_f[i][j] = max(max_f[i][j], max(a, max(b, max(c, d))));
        min_f[i][j] = min(min_f[i][j], min(a, min(b, min(c, d))));
      }
    }
  }
  return max_f[0][nums_size - 1];
}

void test_solution() {
  string exp("5-8+7*4-8+9");
  assert(get_maximum_value(exp) == 200);

}

int main() {
  //test_solution();
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
