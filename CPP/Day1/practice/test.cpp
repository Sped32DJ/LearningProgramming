#include <iostream>
using namespace std;

int main() {
  string fileName;
  cout << "==============================================================\n"
       << "|        Welcome to the Automatic Maze Path Finder!      |\n"
       << "=============================================================\n"
       << "\nEnter the name of the Maze configuration file: ";
  getline(cin, fileName);

  cout << "\nYou entered: " << fileName << endl;
}
