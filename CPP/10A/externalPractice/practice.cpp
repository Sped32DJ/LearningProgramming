#include <iostream>
using namespace std;

int main() {

  int i, j;
  for (i = 0; i < 2; ++i) {
    for (j = i; j < 2; ++j) {
      cout << i << j << ' ';
    }
  }
  cout << endl;

  return 0;
}
