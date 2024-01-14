#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>


using std::min;
using std::max;
using std::abs;
using std::string;
using std::vector;

struct Point {
  int x;
  int y;
  long double distance_to(Point o) {
    return sqrt((long double)(x - o.x) * (x - o.x) + (y - o.y) * (y - o.y));
  }
};

long double try_min_distance(vector<Point>& points);                         

long double minimal_distance(vector<int> x, vector<int> y) {
  vector<Point> points(x.size());
  for (int i= 0; i < x.size(); i++) points[i] = Point{x[i], y[i]};
  sort(points.begin(), points.end(), [](Point &a, Point &b) -> bool {return a.y < b.y;});
  return try_min_distance(points);
}


long double try_min_distance(vector<Point>& points_y_order) {

  if (points_y_order.size() <= 1) {
    return std::numeric_limits<long double>::infinity();
  } else if (points_y_order.size() == 2) {
    return points_y_order[0].distance_to(points_y_order[1]);
  }
  int pivot_x = points_y_order[rand() % points_y_order.size()].x;
  vector<Point> left_points_y_orders;
  vector<Point> right_points_y_orders;
  
  for (int i = 0; i < points_y_order.size(); i++) {
    if (points_y_order[i].x == pivot_x) rand() % 2 == 0 ? left_points_y_orders.push_back(points_y_order[i]): right_points_y_orders.push_back(points_y_order[i]);
    else if (points_y_order[i].x < pivot_x) left_points_y_orders.push_back(points_y_order[i]);
    else (right_points_y_orders).push_back(points_y_order[i]);
  }

  long double d_left = try_min_distance(left_points_y_orders);
  long double d_right = try_min_distance(right_points_y_orders);
  long double min_distance = min(d_left, d_right);
  vector<Point> left_strip(0);
  vector<Point> right_strip(0);
  vector<Point> total_strip(0);

  int i, j, k;

  for (i = 0; i < (left_points_y_orders).size(); i++) if ((left_points_y_orders)[i].x > pivot_x - min_distance) left_strip.push_back((left_points_y_orders)[i]);
  for (j = 0; j < (right_points_y_orders).size(); j++) if ((right_points_y_orders)[j].x < pivot_x + min_distance) right_strip.push_back((right_points_y_orders)[j]);
  total_strip.resize(left_strip.size() + right_strip.size());
  for (k = 0, i = 0, j = 0; k < total_strip.size(); k++) {
    if (i == left_strip.size()) total_strip[k] = right_strip[j++];
    else if (j == right_strip.size()) total_strip[k] = left_strip[i++];
    else if (left_strip[i].y <= right_strip[j].y) total_strip[k] = left_strip[i++];
    else total_strip[k] = right_strip[j++];
  }

  for (i = 0; i < total_strip.size(); i++) {
    for (j = i + 1; j < total_strip.size(); j++) {
      if (total_strip[j].y - total_strip[i].y > min_distance) break;
      long double tmp_d = total_strip[i].distance_to(total_strip[j]);
      if (tmp_d < min_distance) {
        min_distance = tmp_d; 
      }
    }
  }
  return min_distance;
}

long double native_minimal_distance(vector<int> &x, vector<int> &y) {
  long double min_d = std::numeric_limits<long double>::infinity();
  for (int i = 0; i < x.size() - 1; i++) {
    for (int j = i + 1; j < x.size(); j ++) {
      long double tmp_d = sqrt((long double)(x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
      if (tmp_d < min_d) {min_d = tmp_d;}
    }
  }
  return min_d;
}

void test_solution() {
  vector<int> x;
  vector<int> y;
  for (int n = 10; n < 1000; n++) {
    x.clear();
    y.clear();
    std::cout << n << ": ";
    for (int i = 0; i < n; i++) {
      x.push_back(rand() % 10);
      y.push_back(rand() % 10);
      std::cout << " (" << x[i] << " " << y[i] << ") "; 
    }
    std::cout << std::endl;
    long double real = minimal_distance(x, y);
    long double expected = native_minimal_distance(x,y);
    assert(abs(real - expected) < 0.000001);
    
  }
}

void test_solution2() {
  vector<int> x{2, 3, 0, 3, 4, 1, 3};
  vector<int> y{2, 1, 0, 1, 2, 3, 4};
  long double real = minimal_distance(x, y);
  long double expected = native_minimal_distance(x,y);
  assert(abs(real - expected) < 0.000001);

}


int main() {
  //test_solution2();
  //test_solution();
  size_t n;
  std::cin >> n;
  vector<int> x(n);
  vector<int> y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(19) << minimal_distance(x, y) << "\n";
}
