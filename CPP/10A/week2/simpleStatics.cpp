#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
   int in1, in2, in3, prod;
   double sum, avg, avg2;

   cin >> in1 >> in2 >> in3;

   sum  = in1 + in2 + in3;
   avg  = (in1 + in2 + in3) / 3;
   prod = in1 * in2 * in3;

  //cout << fixed << setprecision(3);

   cout << sum << ' ' << avg << ' ' << prod << endl;
   /* Type your code here. */

   avg2  = (in1 + in2 + in3) / 3.0;

   cout << sum << ' ' << avg2 << ' ' << prod << endl;

   // outputting distance between each number
   cout << fixed << setprecision(0);
   cout << abs(avg - in1) << ' ' << abs(avg - in2) << ' ' << abs(avg - in3) << endl;

   return 0;
}

