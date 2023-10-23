#include <iostream>
#include <string>
using namespace std;

template<typename TheType>
TheType TripleMin(TheType item1, TheType item2, TheType item3) {
   TheType minVal = item1; // Holds min item value, init to first item

   if (item2 < minVal) {
      minVal = item2;
   }
   if (item3 < minVal) {
      minVal = item3;
   }

   return minVal;
}

int main() {
   int num1 = 55;       // Test case 1, item1
   int num2 = 99;       // Test case 1, item2
   int num3 = 66;       // Test case 1, item3

   char let1 = 'a';     // Test case 2, item1
   char let2 = 'z';     // Test case 2, item2
   char let3 = 'm';     // Test case 2, item3

   string str1 = "zzz";    // Test case 3, item1
   string str2 = "aaa";    // Test case 3, item2
   string str3 = "mmm";    // Test case 3, item3

   // Try TripleMin function with ints
   cout << "Items: " << num1 << " " << num2 << " " << num3 << endl;
   cout << "Min: " << TripleMin(num1, num2, num3) << endl << endl;

   // Try TripleMin function with chars
   cout << "Items: " << let1 << " " << let2 << " " << let3 << endl;
   cout << "Min: " << TripleMin(let1, let2, let3) << endl << endl;

   // Try TripleMin function with strings
   cout << "Items: " << str1 << " " << str2 << " " << str3 << endl;
   cout << "Min: " << TripleMin(str1, str2, str3) << endl << endl;

   return 0;
}
