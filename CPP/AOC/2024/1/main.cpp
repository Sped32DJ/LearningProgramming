#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  string input = "input.txt";
  if (argc > 1) {
    input = argv[1];
  }

  string line;
  fstream file(input);

  while (getline(file, line)) {
  }
  return 0;
}
