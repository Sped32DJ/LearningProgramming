#include <iostream>
#include <vector>
using namespace std;

#include <iostream>
#include <vector>
using namespace std;

int main() {
   int numDistance;
   double firstDistance;
   double lastDistance;
   unsigned int i;

   cin >> numDistance;
   cin >> firstDistance;
   cin >> lastDistance;

   /* Your code goes here */

   for (i = 0; i < swimmingNumbers.size(); ++i) {
      cout << swimmingNumbers.at(i) << " ";
   }
   cout << endl;

   return 0;
}

// Exercise 1
/* int main() {
  double distance1;
  double distance2;
  double distance3;
  double distance4;
  unsigned int i;

  cin >> distance1;
  cin >> distance2;
  cin >> distance3;
  cin >> distance4;

  vector<double> swimmingDistance(4);

  swimmingDistance.at(0) = distance4;
  swimmingDistance.at(1) = distance3;
  swimmingDistance.at(2) = distance2;
  swimmingDistance.at(3) = distance1;

  for (i = 0; i < swimmingDistance.size(); ++i) {
    cout << swimmingDistance.at(i) << " ";
  }
  cout << endl;

  return 0;
} */
