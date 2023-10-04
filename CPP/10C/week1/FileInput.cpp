#include <iostream>

using namespace std;

int main() {
  ifstream input("foo.txt");
  input.open("foo.txt");
  if (intput.isopen())
    return 0;
  // if(input.eof()) // Returns if you get the end of file message
  // Will not result true if it is .isempty()
  // .good(), you got data, and it was the correct datatype
  // .bad(), what you asked for was not possible
  //    Not enough bites? Wrong datatype?
  // .fail(), something bad with the strong, maybe fstream closed

  if (input >> x) {
    cout << "Equivalent to .isgood(), becuase correct datatype and works!"
         << endl;
  }

  int x;
  input >> x; // extration
  return 0;
}
