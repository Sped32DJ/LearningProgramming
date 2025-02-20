#include <vector>

using namespace std;

class Solution {
public:
  int rodCutTopDownRef(int price[], int n) {
    int val[n + 1];
    val[0] = 0;
    int i, j;
    for (i = 1; i <= n; i++) {
      int max_val = 0;
      for (j = 1; j < i; j++)
        max_val = max(max_val, price[j] + val[i - j - 1]);
      val[i] = max_val;
    }
    return val[n];
  }

  int rodCutTopDownHelp(vector<int> r, int n) {
    // Initialize r[] with trash values
    for (int i = 0; i < n; i++) {
      r[i] = 0;
    }
    return rodCutTopDown(r, n); // Asks for the value for rod length n
  }

  int rodCutTopDown(vector<int> r, int i) {
    // Base case
    if (i == 0)
      return 0;
    // If the value is already calculated, return it
    if (r[i] > 0)
      return r[i];
    int q = 0; // Holds max

    for (int j = 1; j < i; j++) {
      // It is either the current max or the new max
      // It knows the value of r[j] but asks for the value of [i-j]
      q = max(q, r[j] + rodCutTopDown(r, i - j));
    }
    r[i] = q; // Updates the DP table with the max value
    return q; // Returns the max value
  }
  int rodCutBottomUpRef(int price[], int n) {
    int val[n + 1];
    val[0] = 0;
    int i, j;
    for (i = 1; i <= n; i++) {
      int max_val = 0;
      for (j = 1; j < i; j++)
        max_val = max(max_val, price[j] + val[i - j - 1]);
      val[i] = max_val;
    }
    return val[n];
  }

  int rodCutBottomUp(int price[], int n) {
    // Initiliaze dp table r[] with 0
    int r[n + 1];
    for (int i = 0; i < n; ++i) {
      r[i] = 0;
    }

    // Bottom up approach
    // Two for loops to check every solution possible
    // The difference is that we have a DP table to store past results
    for (int i = 1; i < n; ++i) {
      // Holds the max
      int q = 0;
      for (int j = 1; j < i; ++j) {
        // Updates the max
        q = max(q, price[j] + r[i - j]);
      }
      r[i] = q;
    }

    return r[n];
  }
};
