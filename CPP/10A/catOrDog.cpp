#include <iostream>
#include <string>
using namespace std;

int main() {

  string s;

  s = "cat";

  cout << s.size() << endl;
  cout << s.at(0) << endl;
  cout << s.at(s.size()-1) << endl; // Like python using [-1] with (.size()-1)

  s.at(0) = 'm';

  cout << s << endl;

  // .find, give index of where string first appears
  cout << s.find( "at") << endl;

  if ( s.find( "a") != string::npos){
      cout << "\nIt was found!";
      cout << endl << "It was found!";
      cout << "\tIt was found!";
  } else {
      cout << "\nIt was not found ;(";
  }
  cout << endl;
/*
  cout << s.find( "dog") << endl;
  cout << string::npos << endl; // this constant is usedful
*/
  return 0;
}
