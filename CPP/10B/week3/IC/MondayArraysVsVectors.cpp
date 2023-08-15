// Arrays vs vectors
/* - different syntax for declaring
 * - cannot change size once its declared
 * - array is not a class (no lib required)
 *   - no member functions at all (at,size,push_back, etc)
 * - arrays are passed in to functions differently (already passed in by passed
 * in by reference without ampersand)
 * - no bounds checking
 *   - when trying to access out of bounds, we get undefined behavrio
 *   UNDEFINED BEHAVIOR IS THE WORST ERROR
 *      -possible behaviors when going out of bounds of array
 *       - could change value of other variable
 *       - out of range, prints out index, and illegal index
 *       - segmentation fault (program crash)
 *       - everything works normally (correct logic)
 * - we need to double check everything
 * - keep track of size using variables
 * */

#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, *argv[]) {

  if (arc < 2) {
    cout << "USAGE: " << argv[0] << " input_file" << endl;
    return 1;
  }
  ifstream inFS(argv[1]);
  if (!fin.is_open()) {
    cout << "Error opening " << argv[1] << endl;
    return 1;
  }

  return 0;
}
