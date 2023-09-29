#include <iostream>
#include <vector>

class Solution {
public:
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    vector<int> merged;

    // size is correct
    size_t size;
    if (m > n)
      size = m;
    else
      size = n;

    // something with push_back failed
    for (size_t i = 0; i < size; ++i) {
      if (i < m) {
        merged.push_back(nums1.at(i));
        cout << "num1 [" << i << "]: " << nums1.at(i) << endl;
      }
      if (i < n) {
        merged.push_back(nums2.at(i));
        cout << "num2 [" << i << "]: " << nums2.at(i) << endl;
      }
    }
  }
};
