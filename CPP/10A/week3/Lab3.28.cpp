#include <iostream>
using namespace std;

int main() {

  int highwayNum;
  cin >> highwayNum;

  if (highwayNum >= 1 && <= 99) {
    cout << "I- " << highwayNum << " is primary, going ";
    if (highwayNum % 2 == 0) {
      cout << "east/west";
    } else {
      cout << "north/south";
    }
  }
  cout << endl;

  return 0;
}
