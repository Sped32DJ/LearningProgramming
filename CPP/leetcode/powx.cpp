using namespace std;
class Solution {
public:
  // x = value
  // n = n power
  double myPow(double x, int n) {
    if (n == 0) {
      return 1;
    }
    // Given a negative power
    if (n < 0) {
      return 1 / x * myPow(1 / x, -(n + 1));
    } else {
      // Positive powers
      return myPow(x * x, n / 2) * (n % 2 == 0 ? 1 : x);
    }
    return 0;
  }
};
