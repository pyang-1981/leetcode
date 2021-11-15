#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

/* Use a map
*  {
      '(': i,
      ')': j
   } 
*  to represent the current available left and right parentheses.
* Use an integer layer to represent the number of open left parentheses,
* e.g., ( has layer == 1, (()) has layer == 0, (( has layer == 2, etc.
*
* We use DFS to get all the valid parenthese strings.
* At each step, we first try '(' if it is available, and update
* layer + 1, --avail['('].
* Then, we try ')' if it is available and
  layer != 0 (We can not have a open right parenthese) and update
* layer - 1, --avail[')'].
*/

void genParen(string& s, int layer, map<char, int>& avail, int n, vector<string> &res) {
    if (avail['('] > 0) {
        s.push_back('(');
        --avail['('];
        if (s.size() == 2 * n) {
            res.push_back(s);
        } else {
            genParen(s, layer + 1, avail, n, res);
        }
        // Restore context.
        s.pop_back();
        ++avail['('];
    }
    if (layer != 0 && avail[')'] > 0) {
        s.push_back(')');
        --avail[')'];
        if (s.size() == 2 * n) {
            res.push_back(s);
        } else {
            genParen(s, layer - 1, avail, n, res);
        }
        s.pop_back();
        ++avail[')'];
    }
}

vector<string> solu(int n)
{
    string s;
    map<char, int> avail = {{'(', n}, {')', n}};
    vector<string> res;

    genParen(s, 0, avail, n, res);

    return res;
}




