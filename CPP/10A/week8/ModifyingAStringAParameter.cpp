#include <iostream>
#include <string>
using namespace std;

void MakeSentenceExcited(string &sentenceText) {
  int pos = sentenceText.find('.');
  while (pos != string::npos) {
    sentenceText.replace(pos, 1, "!");
    pos = sentenceText.find('.', pos + 1);
  }
}

int main() {
  string testStr;

  getline(cin, testStr);
  MakeSentenceExcited(testStr);
  cout << testStr;

  return 0;
}
