#include <string>
using namespace std;

class Solution {
public:
  int LCS(string s1, string s2, int m, int n) {
    // Base case, either string is empty
    if (m == 0 || n == 0)
      return 0;

    // Last chars match
    if (s1.at(m - 1) == s2.at(n - 1)) {
      // So we cut off one from both strings and add 1 to the result
      // We add 1 to the answer and ask if there is any more similarities left
      // in the string
      // All until the base case of either string being empty
      return 1 + LCS(s1, s2, m - 1, n - 1);
    } else {
      // Then you take the max if you remove 1 from left string or right string
      return max(LCS(s1, s2, m - 1, n), LCS(s1, s2, m, n - 1));
    }
  }
};
