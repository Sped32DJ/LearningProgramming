#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ofstream zipCodeFS;
  string nameOfFile;

  int zipcode;
  cin >> nameoffile;

  zipcodefs.open(nameoffile);
  if (!zipcodefs.is_open()) {
    cout << nameoffile << ": file-open operation failure." << endl;
    return 1;
  }

  while(cin>>zipcode){
      zipcodefs << "zip code " << zipcode << endl;
  }

  zipcodefs.close();

  if (zipCodeFS.is_open()) { /* For testing purpose only */
    zipCodeFS << "File is not closed." << endl;
  }

  return 0;
}
