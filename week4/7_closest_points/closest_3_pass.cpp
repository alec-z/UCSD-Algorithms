#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <functional>


using std::min;
using std::max;
using std::abs;
using std::string;
using std::vector;

struct Point {
  int x;
  int y;
  long double distance_to(Point o) {
    if (x == o.x && y == o.y) return 0;
    return sqrt((long double)(x - o.x) * (x - o.x) + (long double)(y - o.y) * (y - o.y));
  }
};

template<typename T>
struct WholeOrderVector {
  vector<T> objects_0_order;
  vector<T> objects_1_order;
  vector<int> index_0_to_1;
};

template<typename T>
void sub_range_by_position(WholeOrderVector<T>&wo_objects, int left_0_pos, int right_0_pos, WholeOrderVector<T>& result) {
  
  int len = right_0_pos - left_0_pos + 1;
  int wo_objects_size = wo_objects.index_0_to_1.size();
  result.objects_0_order.clear();
  result.objects_1_order.clear();
  result.index_0_to_1.resize(len);

  vector<int> index_1_to_0(wo_objects_size, -1);

  for (int i = left_0_pos; i <= right_0_pos; i++) {
    index_1_to_0[wo_objects.index_0_to_1[i]] = i;
    result.objects_0_order.push_back(wo_objects.objects_0_order[i]);
  }

  for (int j = 0; j < wo_objects.objects_1_order.size(); j++) {
    if (index_1_to_0[j] > -1) {
      result.objects_1_order.push_back(wo_objects.objects_1_order[j]);
      int new_1_index = result.objects_1_order.size() - 1;
      int new_0_index = index_1_to_0[j] - left_0_pos;
      result.index_0_to_1[new_0_index] = new_1_index;
    }
  }
};

template<typename T>
int binary_search_SSGT(vector<T> &objects, int left, int right,
                          long double target, const std::function<long double(T &)>& f) {
  if (left > right) return right + 1;
  int mid = (left + right) / 2;
  if (f(objects[mid]) > target) {
    return binary_search_SSGT(objects, left, mid - 1, target, f);
  } else {
    return binary_search_SSGT(objects, mid + 1, right, target, f);
  }
}

template<typename T>
int binary_search_GSST(vector<T> &objects, int left, int right,
                          long double target, const std::function<long double(T&)>& f) {
  if (left > right) return left - 1;
  int mid = (left + right) / 2;
  if (f(objects[mid]) < target) {
    return binary_search_GSST(objects, mid + 1, right, target, f);
  } else {
    return binary_search_GSST(objects, left, mid - 1, target, f);
  }
}

template<typename T>
void sub_range_by_value_SSGT(WholeOrderVector<T> &wo_objects, long double target, const std::function<long double(T&)>& f, WholeOrderVector<T> &result) {
  int SSGT_pos = binary_search_SSGT<T>(wo_objects.objects_0_order, 0, wo_objects.objects_0_order.size() - 1, target, f);
  return sub_range_by_position<T>(wo_objects, SSGT_pos, wo_objects.objects_0_order.size() -1, result);
};

template<typename T>
void sub_range_by_value_GSST(WholeOrderVector<T> &wo_objects, long double target, const std::function<long double(T&)>& f, WholeOrderVector<T> &result) {
  int GSST_pos = binary_search_GSST<T>(wo_objects.objects_0_order, 0, wo_objects.objects_0_order.size() - 1, target, f);
  return sub_range_by_position<T>(wo_objects, 0, GSST_pos, result);
};

long double try_min_distance(WholeOrderVector<Point>& wo_points) {

  if (wo_points.objects_0_order.size() <= 1) {
    return std::numeric_limits<long double>::max();
  } else if (wo_points.objects_0_order.size() == 2) {
    return wo_points.objects_0_order[0].distance_to(wo_points.objects_0_order[1]);
  }
  int mid = (wo_points.objects_0_order.size() - 1) / 2;
  long double pivot_x = wo_points.objects_0_order[mid].x;
  WholeOrderVector<Point> left_wo_points;
  WholeOrderVector<Point> right_wo_points;

  sub_range_by_position<Point>(wo_points, 0, mid, left_wo_points);
  sub_range_by_position<Point>(wo_points, mid + 1, wo_points.objects_0_order.size() - 1, right_wo_points);

  long double d_left = try_min_distance(left_wo_points);
  long double d_right = try_min_distance(right_wo_points);
  long double min_distance = min(d_left, d_right);
  WholeOrderVector<Point> left_wo_strip;
  WholeOrderVector<Point> right_wo_strip;

  sub_range_by_value_SSGT<Point>(left_wo_points, pivot_x - min_distance, [](Point& p) {return p.x;}, left_wo_strip);
  sub_range_by_value_GSST<Point>(right_wo_points, pivot_x + min_distance, [](Point& p) {return p.x;}, right_wo_strip);

  vector<Point>& left_point_strip = left_wo_strip.objects_1_order;
  vector<Point>& right_point_strip = right_wo_strip.objects_1_order;
  vector<Point> total_point_strip;
  total_point_strip.resize(left_point_strip.size() + right_point_strip.size());
  for (int k = 0, i = 0, j = 0; k < total_point_strip.size(); k++) {
    if (i == left_point_strip.size()) total_point_strip[k] = right_point_strip[j++];
    else if (j == right_point_strip.size()) total_point_strip[k] = left_point_strip[i++];
    else if (left_point_strip[i].y <= right_point_strip[j].y) total_point_strip[k] = left_point_strip[i++];
    else total_point_strip[k] = right_point_strip[j++];
  }

  for(int i = 0; i < total_point_strip.size(); i++) {
    for (int j = i + 1; j < total_point_strip.size(); j++) {
      if (total_point_strip[j].y - total_point_strip[i].y > min_distance) break;
      long double tmp_d = total_point_strip[i].distance_to(total_point_strip[j]);
      if (tmp_d < min_distance) {
        min_distance = tmp_d; 
      }
    }
  }

  return min_distance;
}
                       

long double minimal_distance(vector<int> x, vector<int> y) {
  struct PointYIndex {
    int x;
    int y;
    int y_index;
  };
  WholeOrderVector<Point> wo_points;
  
  vector<PointYIndex> points_y_index(x.size());

  for (int i = 0; i < x.size(); i++) points_y_index[i] = PointYIndex{x[i], y[i]};
  sort(points_y_index.begin(), points_y_index.end(), [](PointYIndex &a, PointYIndex &b) -> bool {return a.y < b.y;});
  for (int i = 0; i < x.size(); i++) {
    points_y_index[i].y_index = i; 
    wo_points.objects_1_order.push_back(Point{points_y_index[i].x, points_y_index[i].y});
  }
  sort(points_y_index.begin(), points_y_index.end(), [](PointYIndex &a, PointYIndex &b) -> bool {return a.x < b.x;});

  for (int i = 0; i < x.size(); i++) {
    wo_points.objects_0_order.push_back(Point{points_y_index[i].x, points_y_index[i].y});
    wo_points.index_0_to_1.push_back(points_y_index[i].y_index);
  }

  return try_min_distance(wo_points);
}


long double native_minimal_distance(vector<int> &x, vector<int> &y) {
  long double min_d = std::numeric_limits<long double>::max();
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
  for (int n = 10; n < 10000; n++) {
    x.clear();
    y.clear();
    std::cout << n << ": ";
    for (int i = 0; i < n; i++) {
      x.push_back(rand() % 10000);
      y.push_back(rand() % 10000);
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
  std::cout << "test 2";

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
  std::cout << std::setprecision(15) << minimal_distance(x, y) << "\n";
}
