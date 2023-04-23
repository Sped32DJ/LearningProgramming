#include <iostream>
using namespace std;

int main() {
  int lightAmount;

  cin >> lightAmount;

  if (lightAmount <= 441) {
    cout << "Too dark";
  } else if (lightAmount <= 2668) {
    cout << "Fine";
  } else {
    cout << "Too bright";
  }
  cout << endl;
  /* Your code goes here */

  return 0;
}
