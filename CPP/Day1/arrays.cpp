#include <cmath>
#include <iostream>

using namespace std;

int main(){

  cout << "test" << endl;
  int luckyNums[20] = {4, 8, 15, 16, 23, 42};
  luckyNums[10] = 100;

  cout << luckyNums[0] << endl;

  int location;
  cout << "Enter Index: ";
  cin >> location;

  cout << luckyNums[location] << endl;

  return 0;
}
