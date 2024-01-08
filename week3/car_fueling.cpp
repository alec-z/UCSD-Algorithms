#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    // write your code here
    int result = 0;
    int last_full_tank_distance = 0;
    stops.push_back(dist);
    for (int i = 0; i < stops.size(); i++) {
        if (stops[i] - last_full_tank_distance > tank) {
            if (i == 0) {
                return -1;
            }
            last_full_tank_distance = stops[i - 1];
            if (stops[i] - last_full_tank_distance > tank) {
                return -1;
            }
            result += 1;
        }
    }
    return result;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
