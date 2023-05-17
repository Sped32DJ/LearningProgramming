#include <iostream>
using namespace std;

int PrintVal(int num1, int num2) {
  int sum = 0;

  // fix the integers (make even)
  if (num1 % 2 != 0) { // first, size up
    ++num1;
  }
  if (num2 % 2 != 0) { // second number, size down
    --num2;
  }

  // inclusive
  while (num1 <= num2) {
    sum += num1;
    num1 += 2;
  }

  cout << sum << endl;
}

int main() {
  int input1;
  int input2;

  cin >> input1;
  cin >> input2;
  PrintVal(input1, input2);

  return 0;
}
