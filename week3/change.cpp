#include <iostream>

int get_change(int m) {
  //write your code here
  int result = 0;
  result += m / 10;
  m %= 10;
  result += m / 5;
  m %= 5;
  result += m / 1;
  return result;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
