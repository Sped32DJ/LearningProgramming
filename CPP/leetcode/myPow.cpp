class Solution {
public:
  double myPow(double x, int n) {
    // base cases
    if (n == 0)
      return 1;
    if (x == 1)
      return 1;

    double val = x;
    if (n < 0) {
      for (size_t i = 0; i < n; ++i) {
        val *= x;
      }
      return val;
    } else {
      val = 1 / x;
      for (size_t i = 0; i < n; ++i) {
        val *= x;
      }
      return val;
    }
  }
};
