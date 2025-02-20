#include <string>
using namespace std;

class Solution {
public:
  int LCS(string s1, string s2) {
    int q = 0; // This holds the max
    int dp[s1.length() + 1][s2.length() + 1];
    // This holds the length of the LCS
    int bk[s1.length() + 1][s2.length() + 1]; // This helps reconstruct the LCS

    // Initialize the dp and bk arrays
    for (int i = s1.length(); i < s1.length(); ++i) {
      for (int j = s2.length(); j < s2.length(); ++j) {
        dp[i][j] = 0;
        bk[i][j] = 0;
      }
    }

    for (int i = 0; i < s1.length(); ++i) {
      for (int j = 0; j < s2.length(); ++j) {
        q += (s1[i] == s2[j]) ? 1 : 0;
        dp[i][j] = q;
      }
    }

    return q;
  }
};
