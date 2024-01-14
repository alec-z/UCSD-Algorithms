#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using std::vector;

struct Node {
  int p_pos; // point's location;
  int p_type; // segment start point is 0, point position is 1, segement end point is 2;
  int index; //points's origin index;
};

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  //write your code here
  auto less = [](Node& a, Node& b) -> bool {
    if (a.p_pos == b.p_pos) return a.p_type < b.p_type;;
    return a.p_pos < b.p_pos; 
  };
  vector<Node> all_points;
  for (int i = 0; i < starts.size(); i++) all_points.push_back(Node{starts[i], 0, -1});
  for (int i = 0; i < ends.size(); i++) all_points.push_back(Node{ends[i], 2, -1});
  for (int i = 0; i < points.size(); i++) all_points.push_back(Node{points[i], 1, i});
  sort(all_points.begin(), all_points.end(), less);
  int current_segements = 0;
  for (int i = 0; i < all_points.size(); i++) {
    if (all_points[i].p_type == 0) current_segements++;
    else if (all_points[i].p_type == 2) current_segements--;
    else cnt[all_points[i].index] = current_segements;

  }

  return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}
void test_solution() {
  vector<int> starts{0,7};
  vector<int> ends{5, 10};
  vector<int> points{1, 6, 11};
  assert(fast_count_segments(starts, ends, points) == naive_count_segments(starts, ends, points));
}

int main() {
  //test_solution();
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
