#include <vector>

using namespace std;

class Solution {
public:
  int rodCutTopDown(int price[], int n) {
    int val[n + 1];
    val[0] = 0;
    int i, j;
    for (i = 1; i <= n; i++) {
      int max_val = INT_MIN;
      for (j = 0; j < i; j++)
        max_val = max(max_val, price[j] + val[i - j - 1]);
      val[i] = max_val;
    }
    return val[n];
  }

  int rodCutRecurr(vector<int> &price) {
    int n = price.size();

    return rodCutRecurr(price, n); // What is the price of length n?
  }
  int rodCutHelper(vector<int> &price, int i) {
    // Base case
    if (n == 0)
      return 0;

    int maxVal = 0; // -infty

    for (int j = 1; j < i; ++j) {
      // We decide that our maxVal is equal to the curr Max, the price at j
      // + the remaining rod
      maxVal = max(maxVal, price[j] + rodCutHelper(price, i - j - 1));
    }
    return maxVal;

    // int val[n + 1];
    // val[0] = 0;
    // for (int i = 1; i <= n; i++)
    //   val[i] = INT_MIN;
    // return rodCutRecurr(price, n);
  }
};
