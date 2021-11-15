/* Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

    Each row must contain the digits 1-9 without repetition.
    Each column must contain the digits 1-9 without repetition.
    Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.


A partially filled sudoku which is valid.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'. */

#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        set<char> s;
        // Check rows
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == '.') {
                    continue;
                }
                if (s.find(board[i][j]) == s.end()) {
                    s.insert(board[i][j]);
                } else {
                    return false;
                }
            }
            s.clear();
        }
        // Check colums
        for (int i = 0; i < board[0].size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                if (board[j][i] == '.') {
                    continue;
                }
                if (s.find(board[j][i]) == s.end()) {
                    s.insert(board[j][i]);
                } else {
                    return false;
                }
            }
            s.clear();
        }
        // Check sub
        for (int i = 0; i < 9; i += 3) {
            for (int j = 0; j < 9; j += 3) {
               for (int n = i; n < i + 3; n++) {
                   for (int m = j; m < j + 3; m++) {
                       if (board[n][m] == '.') {
                           continue;
                       }
                       if (s.find(board[n][m]) == s.end()) {
                           s.insert(board[n][m]);
                       } else {
                           return false;
                       }
                   }
               }
               s.clear();
            }
        }

        return true;
    }
};