#include <iostream>
using namespace std;

class FizzString {
public:
  FizzString(int i) {}

private:
  int i;
}

int main() {
  int i;
  cin >> i;
  while (i != 0) {
    if (i % 15 == 0) {
      cout << "FizzBuzz\n";
    } else if (i % 3 == 0) {
      cout << "Fizz\n";
    } else if (i % 5 == 0) {
      cout << "Buzz\n";
    } else {
      cout << i << endl;
    }
    cin >> i;
  }
  return 0;
}
