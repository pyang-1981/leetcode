#include <iostream>
#include <string>

using namespace std;

/* Given a parlindromic substr of length 3 and greater with
 * the starting index of i and ending index of j, then
 * the substr from i + 1 to j - 1 is also a palindromic, and
 * the ith char and the jth char are the same. 
 *
 * So, we can initialize a set of initial parlindromic substrs
 * with length 1 and 2, and build longer ones using shorter ones.
 *
 * Let table[i][j] indicate whether the substr from i to j is
 * a parlindromic substr or not. We initialize the table with
 * true or false for all i == j cases (parlindromic with length 1)
 * and all j == i + 1 cases (parlindromic with length 2). Then,
 * from all j == i + k (k from 2 to n - i - 1), we set table[i][j]
 * to true if table[i+1][j-1] is true and the ith char and the jth
 * char are the same. Otherwise, we set the table entry to false.
 */

bool**
init_table(size_t n)
{
  bool **table = new bool*[n];
  for (int i = 0; i < n; i++) {
    table[i] = new bool[n];
  }

  return table;
}

void
destroy_table(bool **table, size_t n)
{
  for (int i = 0; i < n; i++) {
    delete[] table[i];
  }
  delete[] table;
}

int longest_parlindromic_substr(const string &str)
{
  bool **table = init_table(str.size());

  int max = 1;
  for (int i = 0; i < str.size(); i++) {
    table[i][i] = true;
  }

  for (int i = 0; i < str.size() - 1; i++) {
    if (str[i] == str[i+1]) {
      table[i][i+1] = true;
      max = 2;
    }
    else
      table[i][i+1] = false;
  }

  for (int k = 3; k <= str.size(); k++) {
    for (int i = 0; i <= str.size() - k; i++) {
      int j = i + k - 1;
      if (table[i+1][j-1] && str[i] == str[j]) {
        table[i][j] = true;
        max = k;
      } else
        table[i][j] = false;
    }
  }

  destroy_table(table, str.size());
  return max;
}

int main()
{
  string str;
  cin >> str;
  cout << longest_parlindromic_substr(str) << endl;
  return 0;
}
