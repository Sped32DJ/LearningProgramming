#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  int LCSNaive(string s1, string s2, int m, int n) {
    // Base case, either string is empty
    if (m == 0 || n == 0)
      return 0;

    // Last chars match
    if (s1.at(m - 1) == s2.at(n - 1)) {
      // So we cut off one from both strings and add 1 to the result
      // We add 1 to the answer and ask if there is any more similarities left
      // in the string
      // All until the base case of either string being empty
      return 1 + LCSNaive(s1, s2, m - 1, n - 1);
    } else {
      // Check 2 case
      // 1. Exclude last char of s1
      // 2. Excluse last char of s2
      // Then keep the highest value
      return max(LCSNaive(s1, s2, m - 1, n), LCSNaive(s1, s2, m, n - 1));
    }
  }
  int LCS(string s1, string s2, int m, int n, vector<vector<int>> &memo) {
    // Base case; either string empty
    if (m == 0 || n == 0)
      return 0;

    // We already know the answer
    // No need to recalculate
    if (memo[m][n] > 0)
      return memo[m][n];

    // The last two chars do match!
    if (s1[m - 1] == s2[n - 1])
      return 1 + LCS(s1, s2, m - 1, n - 1, memo);

    // Last resort, 2 cases
    // pop last char from string 1
    // pop last char from string 2
    return memo[m][n] =
               max(LCS(s1, s2, m - 1, n, memo), LCS(s1, s2, m, n - 1, memo));
  }
};
