#include <vector>
using namespace std;

class Solution {
public:
  void setZeroes(vector<vector<int>> &matrix) {
    int n = matrix.size();        // Rows
    int m = matrix.at(0).size();  // Columns
    vector<bool> dprow(n, false); // Just holds bools for the rows with 0s
    vector<bool> dpcol(m, false); // Holds 0s for cols with

    // Can be more efficient and just refuse to scan
    // lines that have already been marked as 0
    for (int i = 0; i < n; ++i) {
      // Skips row if tagged
      if (dprow.at(i)) {
        continue;
      }
      for (int j = 0; i < m; ++j) {
        // Skips column if tagged
        if (dprow.at(i) || dpcol.at(j)) {
          continue;
        }
        if (matrix.at(i).at(j) == 0) {
          dprow.at(i) = true;
          dpcol.at(j) = true;
        }
      }
    }

    // Setting rows to 0
    for (int i = 0; i < n; ++i) {
      if (dprow.at(i)) {
        for (int j = 0; j < m; ++j) {
          matrix.at(i).at(j) = 0;
        }
      }
    }
    // Setting Columns to 0
    for (int j = 0; j < m; ++j) {
      if (dpcol.at(j)) {
        for (int i = 0; i < n; ++i) {
          matrix.at(i).at(j) = 0;
        }
      }
    }
  }
};
