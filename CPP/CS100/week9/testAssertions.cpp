#include <iostream>

#define NDEBUG
#include <cassert>
using namespace std;

int main() {
  assert(2 + 2 == 3 + 1);
  cout << "Expression is valid.. Execution continous.\n";
  assert(2 + 2 == 1 + 1);
  cout << "Assert disabled..execution continues with invalid expression\n";
  return 0;
}
