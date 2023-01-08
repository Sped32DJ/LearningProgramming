#include <iostream>
using namespace std;

int main() {

  int x;
  int y;
  cout << "x: ";
  cin >> x;
  cout << "y: ";
  cin >> y;

  int numberGrid[3][2] = {// 3x2 array grid
                          {1, 2},
                          {3, 4},
                          {5, 6}};
  cout << numberGrid[x][y] << "\n" << endl;

  for(int i = 0; i < 3; i++){
      for(int j = 0; j < 2; j++){
          cout << numberGrid[i][j];
      };
      cout << endl;
  };
  return 0;
}
