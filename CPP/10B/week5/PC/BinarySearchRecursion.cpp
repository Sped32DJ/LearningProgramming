#include <iostream>
using namespace std;

void FindNumber(int number, int lowVal, int highVal) {
   int midVal;

   midVal = (highVal + lowVal) / 2;
   cout << number;
   cout << " ";
   cout << midVal;

   if (number == midVal) {
      cout << " a" << endl;
   }
   else {
      if (number < midVal) {
         cout << " b" << endl;
         FindNumber(number, lowVal, midVal);
      }
      else {
         cout << " c" << endl;
         FindNumber(number, midVal + 1, highVal);
      }
   }
}

int main() {
   int number;

   cin >> number;
   FindNumber(number, 0, 8);

   return 0;
}
