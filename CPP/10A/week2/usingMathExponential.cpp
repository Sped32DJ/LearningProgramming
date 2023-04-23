#include <iostream>
#include <cmath>
using namespace std;

int main() {
   double x;
   double y;
   double z;

   cin >> x >> y >> z;

   // x^z, x^y^z, abs(y), sqrt(xy^z)
   cout << pow(x,z) << ' ' <<
   pow(x , pow(y , z)) << ' ' <<
   abs(y) << ' ' <<
   sqrt(pow(x * y,z)) << endl;

   // 2^2^4
   cout << pow(2,pow(2,4));
   /* Type your code here. Note: Include the math library above first. */

   return 0;
}

