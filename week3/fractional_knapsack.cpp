#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;
  vector<double> unit_values(weights.size());
  vector<int> pos(weights.size());
  for (int i = 0; i < weights.size(); i++){
    unit_values[i] = (double)values[i] / weights[i];
    pos[i] = i;
  }
  auto less = [&unit_values](int i, int j) -> bool {return unit_values[i] > unit_values[j]; };
  std::sort(pos.begin(), pos.end(), less);
  for (int i = 0; capacity > 0 && i < pos.size(); i++) {
    int num = pos[i];
    int cur_take = std::min(capacity, weights[num]);
    value += cur_take * unit_values[num];
    capacity -= weights[num];
  }
  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
