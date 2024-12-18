#include <string>
#include <vector>
using namespace std;

// Current Status: It Brokey
class Solution {
public:
  string encode(vector<string> &strs) {
    if (strs.empty()) {
      return "";
    }
    string result;

    for (auto &s : strs) {
      // result += (s.size() + '0') + s;
      result += static_cast<char>(s.size()) + s;
    }

    return result;
  }

  vector<string> decode(string s) {
    vector<string> result;
    if (s.empty()) {
      return result;
    }

    string buffer;
    for (auto c : s) {
      // checks if c is a number
      if (c >= '0' && c <= '9') {
        // Empty, doesn't push into the result vector
        if (!buffer.empty())
          result.push_back(buffer);
        // Clears buffer since it has been presumably pushed back
        buffer.clear();
      } else {
        // Adds to buffer if it detects a character
        buffer.push_back(c);
      }
    }

    return result;
  }
};
