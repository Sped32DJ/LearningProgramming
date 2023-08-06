#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ofstream dataFS;
  string dataFileName;
  /* Additional variable declarations go here */
  cin >> dataFileName;
  int value;
  dataFS.open(dataFileName);

  if (dataFS.is_open()) {
    for (size_t i = 0; i < 3; ++i) { // Ok, I cheated, it is 2am on a Wednesday :sob:
      cin >> value; // nvm, you are meant to read 3 integers from the user
      dataFS << "# " << value << endl;
    }
  } else {
    cout << dataFileName << " could not be opened\n";
  }
  dataFS.close();

  /* Your code goes here */

  if (dataFS.is_open()) { /* For testing purpose only */
    dataFS << "File is not closed." << endl;
  }

  return 0;
}

/* #include <iostream>
#include <fstream>
using namespace std;

int main() {
   ofstream outFS;
   string dataFileName;
   double pineappleQuantity;

   cin >> dataFileName;
   cin >> pineappleQuantity;

   outFS.open(dataFileName);

   if(outFS.is_open()){
       outFS << pineappleQuantity << " kilograms of pineapples\n";
   } else{
       cout << dataFileName << ": error opening file" << endl;
   }

   outFS.close();

   return 0;
} */

/* #include <iostream>
#include <fstream>
using namespace std;

int main() {
   ofstream dataFS;
   double bananaCount;
   string guestName;

   cin >> bananaCount;
   cin >> guestName;

   dataFS.open("data.txt");
   if (!dataFS.is_open()) {
      cout << "data.txt" << ": failed to open file" << endl;
      return 1;
   }

   dataFS << "Shopping List:\n";
   dataFS << bananaCount << " kilograms of bananas for " << guestName << endl;


   dataFS.close();

   return 0;
} */
