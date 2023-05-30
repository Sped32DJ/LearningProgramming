#include <iomanip> // For setprecision
#include <iostream>
using namespace std;

double LapsToMiles(double laps) { return laps / 4.0; }

int main() {
  /* Type your code here. Your code must call the function.  */
  double trackLaps;
  cin >> trackLaps;

  cout << fixed << setprecision(2);
  cout << LapsToMiles(trackLaps) << endl;

  return 0;
}
