#include <string>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  string minWindow(string s, string t) {
    unordered_map<char, int> count_map;
    for (auto c : t) {
      count_map[c]++;
    }

    int win_start = 0, win_end = 0;
    while (win_start < s.size() &&
           count_map.find(s[win_start] == count_map.end())) {
      win_start++;
    }

    count = count_map.size();
    string res;
    for (win_end = win_start; win_end < s.size(); win_end++) {
      if (count_map.find(s[win_end]) != count_map.end() &&
          count_map[s[win_start]] > 0) {
        count_map[s[win_end]]--;
        count--;
      }

      if (count == 0) {
        auto tmp = s.substr(win_start, win_end - win_start + 1);
        if (res.size() == 0 || tmp.size() < res.size()) {
          res = tmp;
        }
        count_map[s[win_start]]++;
        win_start++;
        count++;
        while (win_start < s.size() &&
               count_map.find(s[win_start]) == count_map.end()) {
          win_start++;
        }
        if (win_start > win_end) {
          win_end = win_start;
        }
      }
    }

    return res;
  }
};
