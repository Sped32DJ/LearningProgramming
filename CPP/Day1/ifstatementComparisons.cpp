#include <iostream>

using namespace std;

int getMax(int num1, int num2, int num3) {
  int result;

  if (num1 >= num2 && num1 >= num3) {
    result = num1;
  } else if (num2 >= num1 && num2 >= num3) {
    result = num2;
  } else {
    result = num3;
  }
  // There has to be a 1337 way to get the get the Max num

  /* if (num1 > num2) {
    result = num1;
  } else {
      result = num2;
  } */

  return result;
}

int getMin(int one, int two, int three){

  result Mini;
}
int main() {

  int uno, dos, tres;
  cout << "3 numbers to go into the array: ";
  cin >> uno;
  cin >> dos;
  cin >> tres;
  cout << "Endl\n\n" << endl;

  cout << getMax(uno, dos, tres) << endl;
  cout << getMax(1, 5, 6) << endl;
  cout << "\nPrinting uno dos tres" << endl;
  cout << uno << " " << dos << " " << tres
       << endl; // There is a better way to do this -_-

  return 0;
}
