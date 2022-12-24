#include <iostream>
using namespace std;

main() {

  bool isMale = false;
  bool isTall = true;

  if (isMale && isTall) {
    cout << "You are a tall male" << endl;
  } else if (isMale && !isTall) {
    cout << "You are a short male" << endl;
  } else if (!isMale && isTall) {
    cout << "You are a tall non-male" << endl;
  } else {
    cout << "You are not male or tall" << endl;
  }

  if (isMale || isTall) {
    cout << "You are tall and/or male" << endl;
  } else {
    cout << "You are either/nor tall or male";
  }

  return 0;
}
