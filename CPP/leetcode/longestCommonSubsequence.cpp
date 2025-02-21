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

  // Below is the top down approach with memoization
  int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size();
    int n = text2.size();
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
    return LCS(text1, text2, m, n, memo);
  }
  int LCS(string s1, string s2, int m, int n, vector<vector<int>> &memo) {
    // Base case; either string empty
    if (m == 0 || n == 0)
      return 0;

    // We already know the answer
    // No need to recalculate
    if (memo[m][n] != -1)
      return memo[m][n];

    // The last two chars do match!
    if (s1[m - 1] == s2[n - 1]) {
      memo[m][n] = 1 + LCS(s1, s2, m - 1, n - 1, memo);
    } else {

      // Last resort, 2 cases
      // pop last char from string 1
      // pop last char from string 2
      memo[m][n] =
          max(LCS(s1, s2, m - 1, n, memo), LCS(s1, s2, m, n - 1, memo));
    }
    return memo[m][n];
  }
  // Bottom up Approach
  int LCSBottomUp(string s1, string s2) {
    int n = s1.size();
    int m = s2.size();
    int dp[n + 1][m + 1];
    memset(dp, 0, sizeof(dp)); // Initialize all values to 0

    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (s1.at(i - 1) == s2.at(j - 1)) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }

    return dp[n][m];
  }
};
