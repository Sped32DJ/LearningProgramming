#include <cctype>
#include <iostream>
#include <string>
using namespace std;

int main() {
  string passCode;
  bool isValid;

  getline(cin, passCode);

  /*
  if (isalpha(passCode.at(0)) && isalpha(passCode.at(1))) {
    if (isupper(passCode.at(0)) != isupper(passCode.at(1))) {
      isValid = true;
    } else if (isupper(passCode.at(0)) == isupper(passCode.at(1))){
        isValid = true;
    }
  } else if(islower(passCode.at(0)) && islower(passCode.at(1))){
      if (passCode.at(0) == passCode.at(1)){
          isValid = false;
      }
  }
  else {
    isValid = false;
  } */
  /* Your code goes here */

  if (isalpha(passCode.at(0)) && isalpha(passCode.at(1))){
    if (isupper(passCode.at(0)) || isupper(passCode.at(1))){
        isValid = true;
    }
  } else if (islower(passCode.at(0)) && islower(passCode.at(1))){
      isValid = false;
  }

  cout << passCode.at(0) << ' ' << passCode.at(1) << endl << endl;

  if (isValid) {
    cout << "Valid passcode" << endl;
  } else {
    cout << "Invalid passcode" << endl;
  }

  return 0;
}
