#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
  int singleNumber(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    // Two base cases
    // Only 1 in the array
    if (nums.size() == 1) {
      return nums.at(0);
    }
    // Last and penultimate elements are different
    if (nums.at(nums.size() - 1) != nums.at(nums.size() - 2)) {
      return nums.at(nums.size() - 1);
    }
    for (size_t i = 0; i < nums.size() - 1; i += 2) {
      if (nums.at(i) != nums.at(i + 1)) {
        return nums.at(i);
      }
    }
    return 0;
  }
};
