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
  double distance_to(Point o) {
    return sqrt((x - o.x) * (x - o.x) + (y - o.y) * (y - o.y));
  }
};

double try_min_distance(vector<Point> &points, int left, int right);
int binary_search_celling(vector<Point> &points, int left, int right,
                          double target);
int binary_search_floor(vector<Point> &points, int left, int right,
                          double target);                          

double minimal_distance(vector<int> x, vector<int> y) {
  vector<Point> points(x.size());
  for (int i= 0; i < x.size(); i++) points[i] = Point{x[i], y[i]};
  sort(points.begin(), points.end(), [](Point &a, Point &b) -> bool {return a.x < b.x;});
  return try_min_distance(points, 0, points.size() -1);
}

/*
 * binary_search to get the strip 2 min-distance
 * if is_left, find the leftest position which x - points[position] < d else -1
 * if !is_left, find the rightest position which points[position] - x < d else
 * -1
 */
int binary_search_celling(vector<Point> &points, int left, int right,
                          double target) {
  if (left > right) return right + 1;
  int mid = (left + right) / 2;
  if (points[mid].x > target) {
    return binary_search_celling(points, left, mid - 1, target);
  } else {
    return binary_search_celling(points, mid + 1, right, target);
  }
}

int binary_search_floor(vector<Point> &points, int left, int right,
                          double target) {
  if (left > right) return left - 1;
  int mid = (left + right + 1) / 2;
  if (points[mid].x < target) {
    return binary_search_floor(points, mid + 1, right, target);
  } else {
    return binary_search_floor(points, left, mid - 1, target);
  }
}

double try_min_distance(vector<Point> &points, int left, int right) {
  
  int len = right - left + 1;
  if (len <= 1) {
    return std::numeric_limits<double>::infinity();
  } else if (len == 2) {
    return points[left].distance_to(points[right]);
  }
  int mid = (left + right) / 2;
  double d_left = try_min_distance(points, left, mid);
  double d_right = try_min_distance(points, mid + 1, right);
  double min_distance = min(d_left, d_right);
  int left_pos = binary_search_celling(points, left, mid, points[mid].x - min_distance);
  int right_pos = binary_search_floor(points, mid + 1, right, points[mid].x + min_distance);
  vector<Point> points_y_order(0);
  for (int i = max(left_pos, left); i <= min(right_pos, right); i++) {
    points_y_order.push_back(points[i]);
  }
  sort(points_y_order.begin(), points_y_order.end(), [](Point &a, Point & b) -> bool {return a.y < b.y;});
  for (int i = 0; i < points_y_order.size(); i++) {
    for (int j = i + 1; j < points_y_order.size() && j <= i + 7; j++) {
      if (points_y_order[j].y - points_y_order[i].y > min_distance) break;
      double tmp_d = points_y_order[i].distance_to(points_y_order[j]);
      if (tmp_d < min_distance) {
        min_distance = tmp_d; 
      }
    }
  }
  return min_distance;
}

double native_minimal_distance(vector<int> x, vector<int> y) {
  double min_d = std::numeric_limits<double>::infinity();
  for (int i = 0; i < x.size() - 1; i++) {
    for (int j = i + 1; j < x.size(); j ++) {
      double tmp_d = sqrt((double)(x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
      if (tmp_d < min_d) {min_d = tmp_d;}
    }
  }
  return min_d;
}

void test_solution() {
  vector<int> x;
  vector<int> y;
  for (int n = 2; n < 1000; n++) {
    x.clear();
    y.clear();
    std::cout << n << ": ";
    for (int i = 0; i < n; i++) {
      x.push_back(rand() % 1000);
      y.push_back(rand() % 1000);
      std::cout << " (" << x[i] << " " << y[i] << ") "; 
    }
    std::cout << std::endl;
    double real = minimal_distance(x, y);
    double expected = native_minimal_distance(x,y);
    assert(abs(real - expected) < 0.000001);
    
  }
}

void test_solution2() {
  vector<int> x{2, 3, 0, 3, 4, 1, 3};
  vector<int> y{2, 1, 0, 1, 2, 3, 4};
  double real = minimal_distance(x, y);
  double expected = native_minimal_distance(x,y);
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
  std::cout << std::setprecision(8) << minimal_distance(x, y) << "\n";
}
