#include <iostream>
using namespace std;

class Solution {
public:
  // p[] holds the dimensions of the matrices
  // This is given
  // i is the first matrix
  // j is the last matrix
  // TopDown Order arrangement
  int matMultTD(int p[], int i, int j) {
    // base case, there is only one matrix
    if (i >= j)
      return 0;
    int q = INT_MAX;

    for (int k = i; k < j; ++k) {
      // The minimun is either the current minimun
      // The cost of the left side + the cost of the right side + the cost of
      // the two sides together
      // We don't know the cost of the left or the right, so we just function
      // call (Asking for the answer because we don't know it)
      q = min(q, matMultTD(p, i, k) + matMultTD(p, k + 1, j) +
                     p[i - 1] * p[k] * p[j]);
      p[k] = q;
    }

    return q;
  }
};
