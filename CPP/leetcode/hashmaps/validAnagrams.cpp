#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
  bool isAnagram(string s, string t) {
    if (s.size() != t.size()) {
      return false;
    }

    unordered_map<char, int> countS;
    unordered_map<char, int> countT;

    for (size_t i = 0; i < s.size(); ++i) {
      countS[s[i]]++;
      countT[t[i]]++;
    }
    return countS == countT;
  }
};
