#include <iostream>
using namespace std;

void UpdateRank(char* rankPointer, char rankValue) {

   if (rankPointer == nullptr){
      cout << "rankPointer is null." << endl;
   } else {
      *rankPointer = rankValue; // This finally works!!
   }

}

int main() {
   char rank;
   char* rankPointer;
   char action;
   char value;

   rank = 'Z';
   cin >> action;
   cin >> value;

   if (action == 'Y') {
      rankPointer = &rank;
   }
   else {
      rankPointer = nullptr;
   }

   UpdateRank(rankPointer, value);
	cout << "Rank is " << rank << "." << endl;

   return 0;
}
