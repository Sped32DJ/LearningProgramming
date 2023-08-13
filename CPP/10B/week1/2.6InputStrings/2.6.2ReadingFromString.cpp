#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
   istringstream inSS;
   string userInput;
   string userMonth;
   int userDate;
   int userYear;

   getline(cin, userInput);
   inSS.str(userInput);

   inSS >> userMonth >> userDate >> userYear;

   cout << "Month: " << userMonth << endl
        << "Date: " << userDate << endl
        << "Year: " << userYear << endl;

   return 0;
}
