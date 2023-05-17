#include <iostream>

using namespace std;

int main(){

   int i;
   int j;

   for ( i = 0; i < 3; ++i){

      for ( j = 0; j <= i ; ++j){

         cout << i << ' ';

      }
      if(i != 0){cout << j;}
      cout << endl;
   }

   return 0;
}
