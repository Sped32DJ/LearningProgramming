#include <iostream>
using namespace std;

// Untested code lol
int main() {

  int in;
  int i = 0;

  cin >> in;

  while(in % 11 != 0){
        cout << in << ' ';
        --in;
        ++i;
  }
  cout << in << endl;
  cout << i << endl;

  return 0;
}
