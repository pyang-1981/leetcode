#include <map>
#include <vector>

using namespace std;

vector<vector<int>> twosum(int s, const vector<int> &array)
{
    map<int, bool> m;
    vector<vector<int>> res;
    
    for (auto v : array) {
        if (m.find(s - v) != m.end()) {
            // find a solution.
            res.push_back({v , s - v});
        } else {
            m.insert(make_pair(v, true));
        }
    }

    return res;
}

vector<vector<int>> threesum(int s, const vector<int> &array)
{
    vector<vector<int>> res;

    for (int i = 0; i < array.size(); i++) {
        vector<int> rest(array.begin() + i + 1, array.end());
        vector<vector<int>> temp = twosum(s - array[i], rest);
        if (!temp.empty()) {
            for (const auto &t : temp) {
                vector<int> solu(t.begin(), t.end());
                solu.push_back(array[i]);
                res.push_back(solu);
            }
        }
    }

    return res;
}