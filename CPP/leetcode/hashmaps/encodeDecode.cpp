#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  string encode(vector<string> &strs) {
    string result;

    for (auto &s : strs) {
      // result += (s.size() + '0') + s;
      result += to_string(s.size()) + '#' + s;
    }

    return result;
  }

  vector<string> decode(const string &s) {
    vector<string> result;
    size_t i = 0;

    while (i < s.size()) {
      size_t delimiter = s.find('#', i);
      if (delimiter == string::npos)
        break; // Shouldn't happen if input is valid

      int length = stoi(s.substr(i, delimiter - i)); // Get size prefix
      string str = s.substr(delimiter + 1, length);  // Extract string

      result.push_back(str);
      i = delimiter + 1 + length; // Move to the next part of the encoded string
    }

    return result;
  }
};
