#include <cmath>
#include <iostream>

using namespace std;

int main(){

  cout << "test" << endl;
  int luckyNums[20] = {4, 8, 15, 16, 23, 42};
  luckyNums[10] = 100;

  cout << luckyNums[0] << endl;

  return 0;
}
