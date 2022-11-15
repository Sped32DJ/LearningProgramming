#include <iostream>

using namespace std;

int main(){
    string phrase = "Giraffe Academy";
    string phrasesub;
    phrasesub = phrase.substr(8, 3);
    cout << phrase << endl;
    cout << phrasesub << endl;
//                   0123456789
//    phrase[0] = 'b';
    cout << phrase.find("Academy", 0) << endl;
    cout << phrase.substr(8, 3) << endl ;

    return 0;
}
