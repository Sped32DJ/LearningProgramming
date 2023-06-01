#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  double limeIntensity1;
  double limeIntensity2;
  double intensityDiff;

  cin >> limeIntensity1;
  cin >> limeIntensity2;
  intensityDiff = limeIntensity1 - limeIntensity2;

  cout << right << fixed << setw(16) << setprecision(4) << limeIntensity1
       << endl;
  cout << "- " << setw(14) << limeIntensity2 << endl;

  cout << setfill('=') << setw(16) << "" << endl;
  cout << setfill(' ') << setw(16) << intensityDiff << endl;
  return 0;
}

/* int main() {
  string itemName;
  int itemCount;

  cin >> itemName;
  cin >> itemCount;

  cout << left << setw(19) << setfill('*')<< itemName;
  cout << '%' << setfill('*') << setw(19) << right << itemCount << endl;
  // bag****************%****************844

  return 0;
} */

/* int main() {
   double width;
   double area;

   cin >> width;

        area = width * width;

   cout << fixed << setprecision(5) << setw(9) << left << setfill('0') << width
<< " "
      << fixed << setprecision(4) << area << ' '
      << scientific << setprecision(4) << area << endl;


   return 0;
} */
