#include <iostream>
#include <vector>

class HashT {
  vector<int> table;
  void insertKeyToTable(vector<int> &T, key) {
    int hash = computeHash(key);

    if (hash < size) {
      auto &bucket = table[key];
    }
    for (auto i = bucket.begin(); i != bucket.end(); ++i) {
      if (i->getWord() == key) {
        i->addAppearance(score);
        return;
      }
    }
    bucket.push_front(newWord);
  }
  int computeHash(s) {

    int val = 0;
    for (size_t i = 0; i < s.size(); ++i) {
      val += s.at(i);
    }
    return val % size;
  }

public:
  void insertKey() { insertKeyToTable(vector<int> & table, key); }
};
