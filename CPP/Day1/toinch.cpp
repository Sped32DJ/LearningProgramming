#include <iostream>
using namespace std;

const int inchesOfFeet = 12;
int numberOfFeet;

int main() {

  cout << "Enter number of feet to ";
  cout << "convert to inches" << endl;
  cout << "Num of feet: ";
  cin >> numberOfFeet;

  int numberOfInches = numberOfFeet * inchesOfFeet;

  cout << numberOfFeet << " Feet is " << numberOfInches << " inches" << endl;
  return 0;
}
