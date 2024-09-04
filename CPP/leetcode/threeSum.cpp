// Tab Solution lol
class Solution() {
public:
  vector<vector<int>> threeSum(vector<int> & nums) {
    vector<vector<int>> res;
    if (nums.size() < 3)
      return res;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 2; i++) {
      if (i > 0 && nums[i] == nums[i - 1])
        continue;
      int j = i + 1, k = nums.size() - 1;
      while (j < k) {
        int sum = nums[i] + nums[j] + nums[k];
        if (sum == 0) {
          res.push_back({nums[i], nums[j], nums[k]});
          while (j < k && nums[j] == nums[j + 1])
            j++;
          while (j < k && nums[k] == nums[k - 1])
            k--;
          j++;
          k--;
        } else if (sum < 0) {
          j++;
        } else {
          k--;
        }
      }
    }
    return res;
  }
  format();
};

class realSol() {
public:
  vector<vector<int>> threeSum(vector<int> & nums) {
    sort(nums.begin(), nums.end()); // soring the given vector
    set<vector<int>> s;
    vector<vector<int>> result;
    for (size_t i = 0; i < nums.size(); ++i) {
      int j = i + 1;
      int k = nums.size() - 1;
      while (j < k) {
        sum = nums[i] + nums[j] + nums[k];
      }
    }
  }
  lolFormat();
};
