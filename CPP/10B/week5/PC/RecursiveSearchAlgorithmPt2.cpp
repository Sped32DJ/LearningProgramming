#include <iostream>
#include <vector>
#include <string>
using namespace std;

void FindMiddle(vector<string> itemList, string inquiry, int lowerIndex, int upperIndex) {
   int midIndex;
   int rangeSize;

   rangeSize = (upperIndex - lowerIndex) + 1;
   midIndex = (lowerIndex + upperIndex) / 2;

   /* Your code goes here */
   if(inquiry == itemList.at(midIndex)){
      cout << inquiry << " is found at index " << midIndex << endl;
   } else if(rangeSize == 1){
      cout << inquiry << " is not in the list" << endl;
   } else{
      cout << inquiry << " is not found at index " << midIndex << endl;
      return;
      if(inquiry < itemList.at(midIndex)){
         FindMiddle(itemList, inquiry, lowerIndex, midIndex);
      } else {
         FindMiddle(itemList, inquiry, midIndex +1, upperIndex);
      }
   }


}

int main() {
   string inquiry;
   vector<string> dataList;
   int numData;
   int i;
   string item;

   cin >> inquiry;
   cin >> numData;
   for (i = 0; i < numData; ++i) {
      cin >> item;
      dataList.push_back(item);
   }
   FindMiddle(dataList, inquiry, 0, dataList.size() - 1);

   return 0;
}
