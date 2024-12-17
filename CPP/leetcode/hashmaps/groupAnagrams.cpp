#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {

    // Sort everything into a hashmap
    unordered_map<string, vector<string>> res;
    for (auto &s : strs) {
      string sortedS = s; // serves as my index
      sort(sortedS.begin(), sortedS.end());

      // Hashmap holds all the grouped up anagrams at index sortedS
      res[sortedS].push_back(s);
    }

    // Push into result vector
    vector<vector<string>> result;
    for (auto &pair : res) {
      result.push_back(pair.second);
    }
    return result;
  }
};
