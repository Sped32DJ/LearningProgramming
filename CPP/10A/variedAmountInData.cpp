#include <iomanip>
#include <iostream>
using namespace std;

// take out the max
// Find the average
// Break when a negative is detected
int main() {
  int input, oldin, max;
  double avg;
  double sum = 0.0;
  int i = 0;
  oldin = 0;
  max = 0;

  cin >> input;

  while (input >= 0) {
    if (input > max) {
      max = input;
    }
    sum += input;
    oldin = input;

    cin >> input;
    i++;
  }
  avg = sum / i;

  cout << fixed << setprecision(2);
  cout << max << ' ' << avg << endl;
  return 0;
}
