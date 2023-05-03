#include <iostream>
#include <string>
using namespace std;

int main() {
  string s;
  int num;

  cin >> s;
  cin >> num;

  while (s != "quit") {
    cout << "Eating " << num << ' ' << s
         << " a day keeps you happy and healthy.\n";
    cin >> s;
    cin >> num;
  }

  return 0;
}
