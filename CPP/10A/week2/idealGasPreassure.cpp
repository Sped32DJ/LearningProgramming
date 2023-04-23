#include <iostream>
#include <cmath>

using namespace std;

int main() {
   double P, V, n;
   double Left, Right;
   double a, b, r;

   a = 3.59;
   b = 0.0427;
   r = 8.314;

   cin >> P >> V >> n;

   // 100 + 3.59 * (1^2 / 10^2)
   Left = P + ((a *pow(n,2)) / pow(V,2));
   // 10 - 1 * 0.0427
   Right = V - (n * b); // 100 10 1 >>

   cout << (Left * Right) / (n * r) << endl;
   // cout << "Left: " << Left << " Right: " <<  Right << endl;

   // cout << (P + a * (pow(n,2) / pow( V, 2))) * (V - n * b) << endl;
   /* Type your code here. Note: Include the math library above first.*/
  // 100 10 1 >> 119.808
  // 10 50 2 >> 30.0356
  // 109.2 305.1 0.5 >> 8014.09
  // P + an^2 / V^2
  // V - nb

   return 0;
}
