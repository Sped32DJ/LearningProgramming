#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  int seedVal;
  int smallestTourCapacity;
  int largestTourCapacity;
  int group1;
  int group2;
  int group3;
  int group4;
  int group5;

  cin >> seedVal;
  cin >> smallestTourCapacity;
  cin >> largestTourCapacity;

  srand(seedVal);

  // smallest number (or else begins at 0) + rand() % (range + 1)
  group1 = smallestTourCapacity +
           rand() % (largestTourCapacity - smallestTourCapacity + 1);
  group2 = smallestTourCapacity +
           rand() % (largestTourCapacity - smallestTourCapacity + 1);
  group3 = smallestTourCapacity +
           rand() % (largestTourCapacity - smallestTourCapacity + 1);
  group4 = smallestTourCapacity +
           rand() % (largestTourCapacity - smallestTourCapacity + 1);
  group5 = 50 - group1 - group2 - group3 - group4;

  cout << group1 << endl
       << group2 << endl
       << group3 << endl
       << group4 << endl
       <<"Sum: " <<group5 << endl;

  return 0;
}
/* int main() {
  int seedVal;
  int sidesInput;

  cin >> seedVal;
  cin >> sidesInput;

  srand(seedVal);

  cout << (rand() % sidesInput) + 1 << endl;
  cout << (rand() % sidesInput) + 1 << endl;
  cout << (rand() % sidesInput) + 1 << endl;

  return 0;
} */

/* int main() {
  int seedVal;
  int sum;
  int max;
  int num1;
  int num2;

  cin >> seedVal;
  cin >> max;

  srand(seedVal);

  num1 = rand() % max;
  num2 = rand() % max;

  cout << num1 << endl;
  cout << num2 << endl;
  sum = num1 + num2;
  cout << "Sum: " << sum << endl;

  return 0;
} */
