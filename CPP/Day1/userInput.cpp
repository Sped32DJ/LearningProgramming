#include <iostream>

using namespace std;

int main(){

    string humanname;
    cout << "Enter your name: ";
    getline(cin, humanname);

    cout << "Hello " << humanname << ", Good Morning\n";
    return 0;
}

