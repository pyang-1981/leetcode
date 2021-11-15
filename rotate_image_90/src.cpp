/*You are given an n x n 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

Note:

You have to rotate the image in-place, which means you have
to modify the input 2D matrix directly. DO NOT allocate
another 2D matrix and do the rotation. */

#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

/* Rotating the matrix 90 degree clockwise,
*  means rotating each layer (outer layer, inner layer, etc.)
*  clockwise by its length - 1. 
*/

class CycleIter
{
public:
    friend bool operator==(const CycleIter &m, const CycleIter &n);
    // Create an iterator starting from (row, col) in the matrix.
    CycleIter(vector<vector<int>> &matrix, int row ,int col)
    {
        _matrix = &matrix;
        _starting_row = _row = row;
        _starting_col = _col = col;
    }
    CycleIter(const CycleIter &other) = default;
    int& operator*() const
    {
        return (*_matrix)[_row][_col];
    }
    CycleIter& operator++()
    {
        if (_row == _starting_row && _col != (*_matrix)[0].size() - _starting_row - 1) {
            // We are on the top edge
            ++_col;
        } else if (_col == (*_matrix)[0].size() - _starting_row - 1 && _row != (*_matrix).size() - 1 - _starting_row) {
            // We are on the right edge
            ++_row;
        } else if (_row == (*_matrix).size() - 1 - _starting_row && _col != _starting_row) {
            // We are on the bottom edge
            --_col;
        } else if (_col == _starting_row && _row != _starting_row) {
            // We are on the left edge
            --_row;
        }

        return *this;
    }
    CycleIter operator++(int)
    {
        CycleIter ret = *this;
        this->operator++();
        return ret;
    }
private:
    vector<vector<int>> *_matrix;
    int _row, _col;
    int _starting_row, _starting_col;
};

bool operator==(const CycleIter &m, const CycleIter &n)
{
    return m._matrix == n._matrix && m._row == n._row && m._col == n._col;
}

bool operator!=(const CycleIter &m, const CycleIter &n)
{
    return !(m==n);
}


class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        for (int i = 0; i < matrix.size() / 2; i++) {
            for (int n = 0; n < matrix[0].size() - 2 * i - 1; n++) {
                CycleIter start(matrix, i, 0 + i);
                int tmp = *start;
                CycleIter p = start;
                ++p;
                while (p != start) {
                    swap(*p, tmp);
                    ++p;
                }
                *p = tmp;
            }
        }
    }
};

int main()
{
    //1 2 3 4
    //5 6 7 8
    //9 10 11 12
    //13 14 15 16
    vector<vector<int>> matrix = {{1,2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    Solution().rotate(matrix);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

