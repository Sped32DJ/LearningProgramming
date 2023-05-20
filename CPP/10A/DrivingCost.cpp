#include <iomanip> // For setprecision
#include <iostream>
using namespace std;

/* Define your function here */
double DrivingCost(double milesPerGallon, double dollarsPerGallon, int miles) {
  return (dollarsPerGallon / milesPerGallon) * miles;
}

int main() {
  /* Type your code here */
  double mpg, dpg;
  cin >> mpg >> dpg;

  cout << fixed << setprecision(2);
  cout << DrivingCost(mpg, dpg, 10) << ' ' << DrivingCost(mpg, dpg, 50) << ' '
       << DrivingCost(mpg, dpg, 400) << endl;

  return 0;
}
