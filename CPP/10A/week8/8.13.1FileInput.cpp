#include <iostream>
#include <fstream>
using namespace std;

int main() {
   ifstream dataFS;
   string beetFileName;
   string customerName;
   int beetCount;

   cin >> beetFileName;

   dataFS.open(beetFileName);
   if (!dataFS.is_open()) {
      cout << beetFileName << ": failed to open file" << endl;
      return 1;
   }

   while(!dataFS.eof()){
      dataFS >> customerName;
      dataFS >> beetCount;
      if(!dataFS.fail()){
         cout << customerName << " sold " << beetCount << endl;
      }
   }

   dataFS.close();

   return 0;
}
