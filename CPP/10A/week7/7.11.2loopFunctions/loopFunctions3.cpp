#include <iostream>
using namespace std;

int FindHighestVal(){
    int max = 0;
    int input = 1;
    while(input > 0){
        cin >> input;
        if(input > max){
            max = input;
        }
    }
    return max;
}

int main() {
   int maxVal;

   maxVal = FindHighestVal();

   cout << maxVal << endl;

   return 0;
}
