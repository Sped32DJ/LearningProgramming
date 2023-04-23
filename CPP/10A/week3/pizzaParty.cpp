#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  int ppl;
  int numPizz;
  double cost;

  //  1 person = 1/6 slices;
  //  1 pizza = 6 slices;
  //  6 slices = $14.95;
  cin >> ppl;

  numPizz = ppl / 6;
  if (ppl % 6 > 0) {
    numPizz++;
  }

  cost = numPizz * 14.95;

  cout << "Pizzas: " << numPizz << endl;
  cout << fixed << setprecision(2) << "Cost: $" << cost << endl;

  return 0;
}
