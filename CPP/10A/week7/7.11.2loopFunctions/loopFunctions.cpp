#include <iostream>
#include <string>
using namespace std;

int PrintValue(string word, int value){
    for(size_t i = 0; i < value; ++i){
        cout << word << endl;
    }
}



int main() {
   string str;
   int num;

   cin >> str;
   cin >> num;
   PrintValue(str, num);

   return 0;
}
