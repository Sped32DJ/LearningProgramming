#include "Triangle.h"
#include <iostream>
using namespace std;
int main() {
  Triangle triangle1;
  Triangle triangle2;
  double userBase, userHeight;

  // TODO: Read and set base and height for triangle1 (use SetBase() and
  cin >> userBase >> userHeight;
  triangle1.SetBase(userBase);
  triangle1.SetHeight(userHeight);
  triangle2.GetArea();

  // TODO: Read and set base and height for triangle2 (use SetBase() and
  // SetHeight())
  cin >> userBase >> userHeight;
  triangle2.SetBase(userBase);
  triangle2.SetHeight(userHeight);
  triangle2.GetArea();

  cout << "Triangle with smaller area:" << endl;
  if (triangle1.GetArea() > triangle2.GetArea()) {
    triangle2.PrintInfo();
  } else {
    triangle1.PrintInfo();
  }

  // TODO: Determine smaller triangle (use GetArea())
  //       and output smaller triangle's info (use PrintInfo())

  return 0;
}
