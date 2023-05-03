#include <iostream>
using namespace std;

int main() {
   int inputVal;
   int numDollars;
   int numQuarters;
   int numDimes;
   int numNickels;
   int numPennies;

   cin >> inputVal;


   numDollars = inputVal / 100;
   inputVal -= numDollars * 100;

   numQuarters = inputVal / 25;
   inputVal -= numQuarters * 25;

   numDimes = inputVal / 10;
   inputVal -= numDimes * 10;

   numNickels = inputVal / 5;
   inputVal = numNickels * 5;

   /* numPennies = inputVal; */


   if (numDollars >= 0) {
      cout << numDollars;
      if (numDollars == 1) {
         cout << " dollar" << endl;
      }
      else {
         cout << " dollars" << endl;
      }
   }

   if (numQuarters > 0) {
      cout << numQuarters;
      if (numQuarters == 1) {
         cout << " quarter" << endl;
      }
   }
      else {
         cout << " quarters" << endl;
      }


   if (numDimes > 0) {
      cout << numDimes;
      if (numDimes == 1) {
         cout << " dime" << endl;
      }
      else {
         cout << " dimes" << endl;
      }
   }

   if (numNickels > 0) {
      cout << numNickels;
      if (numNickels = 1) {
         cout << " nickel" << endl;
      }
      else {
         cout << " nickels" << endl;
      }
   }

   if (numPennies > 0) {
      cout << numPennies;
   }
      if (numPennies == 1) {
         cout << " penny" << endl;
      }
      else {
         cout << " pennies" << endl;
      }


   return 0;
}
