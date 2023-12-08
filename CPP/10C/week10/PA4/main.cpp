#include "Jug.h"
#include <iostream>

using namespace std;

int main() {
  string solution;
  Jug head(3, 5, 4, 1, 2, 3, 4, 5, 6);
  if (head.solve(solution) != 1) {
    cout << "Error 3" << endl;
  }
  cout << solution << endl << endl;

  // Test case 2:
  string solution2;
  Jug head2(3, 5, 4, 1, 1, 1, 1, 1, 2);
  if (head2.solve(solution2) != 1) {
    cout << "Error 3" << endl;
  }
  cout << solution2 << endl;

  return 0;
}
