#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  //write your code here
  auto less = [](Segment a, Segment b) { return a.end < b.end;};
  std::sort(segments.begin(), segments.end(), less);
  for (size_t i = 0; i < segments.size(); ++i) {
    if (segments[i].start != -1) {
      points.push_back(segments[i].end);
      for (size_t j = i + 1; j < segments.size(); j++) {
        if (segments[j].start != -1 && segments[j].start <= segments[i].end) {
          segments[j].start = -1;
        }
      }
    }
  }
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
