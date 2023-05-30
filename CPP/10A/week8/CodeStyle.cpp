#include <iostream>
#include <vector>

using namespace std;

int computingStuff(int num) { return num; }

double computeAverage(double sum, double count) {
  double average;
  average = sum / count;
  return average;
}

int main() {
  int sum;
  double num;
  double count;
  cin >> num;

  sum = 0;
  count = 0;
  if (num == -1) {
    cout << "No integers" << endl;
  } else {
    while (num >= 0) {
      cout << computingStuff(num);
      sum += num;
      cin >> num;
      ++count;
      if (num >= 0) {
        cout << ", ";
      }
    }
    cout << endl;
    cout << sum << endl;
    cout << computeAverage(sum, count) << endl;
  }

  return 0;
}
