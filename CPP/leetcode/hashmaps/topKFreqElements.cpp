#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> map;

    // Make a hashmap holding the frequency of each indexed value
    for (auto &s : nums) {
      ++map[s];
    }

    // Orders the numbers by frequency
    vector<pair<int, int>> arr;
    for (const auto &p : map) {
      arr.push_back({p.second, p.first});
    }
    sort(arr.rbegin(), arr.rend());

    // Holds the result of (frequency >= k) values
    vector<int> result;
    for (size_t i = 0; i < k; ++i) {
      result.push_back(arr[i].second);
    }
    return result;
  }
};
