/*Given an array of strings, group anagrams together.

Example:

Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note:

    All inputs will be in lowercase.
    The order of your output does not matter.

*/

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vector<string>> m;
        for (const auto &s : strs) {
            auto k = s;
            sort(k.begin(), k.end());
            m[k].push_back(s);
        }
        vector<vector<string>> r;
        for (const auto& [k, v] : m) {
            r.push_back(v);
        }
        return r;
    }
};

int main()
{
    vector<string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
    auto r = Solution().groupAnagrams(strs);

    for (const auto &v : r) {
        for (const auto &s : v) {
            cout << s << " ";
        }
        cout << endl;
    }
    return 0;
}