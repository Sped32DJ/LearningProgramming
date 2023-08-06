#include <iostream>
#include <vector>
using namespace std;

/* Declare your function here */
void exactChange( int inVal, vector<int>& vChange);


int main() {
   int inputVal;
   vector<int> changeAmount(4);
   cin >> inputVal;
   exactChange(inputVal, changeAmount);

   // exactChange.at(0) = pennies
   // 1 nickles
   // 2 dimes
   // 3 quarters
   /* Type your code here. Your code must call the function. */
   /* for(size_t i = 0; i < changeAmount.size(); ++i){
       cout << changeAmount.at(i) << ' ';
   }
   cout << endl; */

   return 0;
}

void exactChange( int inVal, vector<int>& vChange){
    /* int temp; */
    if(inVal == 0){
        cout << "no change" << endl;
    }

    // Quarters
    if( inVal / 25 > 1){
        /* cout << inVal/ 25 << " quarters" << endl; */
        vChange.at(3) = inVal / 25;
        inVal -= ( inVal/ 25) * 25;
    } else if( inVal / 25 > 0){
        /* cout << inVal/ 25 << " quarter" << endl; */
        vChange.at(3) = inVal / 25;
        inVal -= ( inVal/ 25 ) * 25;
    }

    // dimes
    if(inVal / 10 > 1){
        /* cout << inVal/ 10 << " dimes" << endl; */
        vChange.at(2) = inVal / 10;
        inVal -= ( inVal/ 10) * 10;
    } else if(inVal / 10 > 0){
        /* cout << inVal/ 10 << " dime" << endl; */
        vChange.at(2) = inVal / 10;
        inVal -= (inVal/ 10) * 10;
    }

    // nickles
    if(inVal / 5 > 0){
        /* cout << inVal/ 5 << " nickle" << endl; */
        vChange.at(1) = inVal / 5;
        inVal -= (inVal/ 5) * 5;
    }

    // pennies
    if(inVal > 1){
        /* cout << inVal << " pennies" << endl; */
        vChange.at(0) = inVal;
    } else if (inVal == 1){
        /* cout << inVal << " penny" << endl; */
        vChange.at(0) = inVal;
    }

    // Printing out Values
    //pennies(0)
    if (vChange.at(0) > 1){
        cout << vChange.at(0) << " pennies" << endl;
    } else if(vChange.at(0) > 0){
        cout << vChange.at(0) << " penny" << endl;
    }
    //nickles(1)
    if(vChange.at(1) > 0){
        cout << vChange.at(1) << " nickel" << endl;
    }
    //dimes(2)
    if(vChange.at(2) > 1){
        cout << vChange.at(2) << " dimes" << endl;
    } else if(vChange.at(2) > 0){
        cout << vChange.at(2) << " dime" << endl;
    }
    //quarters(3)
    if(vChange.at(3) > 1){
        cout << vChange.at(3) << " quarters" << endl;
    } else if (vChange.at(3) > 0){
        cout << vChange.at(3) << " quarter" << endl;
    }

}
