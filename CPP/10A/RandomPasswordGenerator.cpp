#include <cstdlib>
#include <iostream>
using namespace std;

int main() {

  size_t userIn;
  srand(44);

  cin >> userIn;
  cout << rand(userIn);

  return 0;
}
