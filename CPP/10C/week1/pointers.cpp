#include <iostream>
using namespace std;

int main() {
  int *p = nullptr; // pointer integer, just a memory addr
  int q = 10;
  int z = 20;

  p = &q;             // pointing to the addr where q is located.
                      // It is pointing at q
  cout << *p << endl; // Prints out to where p is pointing
                      // I am responsible for deleting everything
                      //        That I place in the heap

  Point *p = new Point[10];
  delete[] p; // If you reserve with [], you must delete with []

  Point *middle = &(p[5]);

  cout << middle[-1].x << endl;
  return 0;
}
