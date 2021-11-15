/*
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

Example 1:

Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:

Input:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
*/

#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

class SpiralIter
{
public:
    friend bool operator==(const SpiralIter &m, const SpiralIter &n);
    // Create an iterator starting from (row, col) in the matrix.
    SpiralIter(vector<vector<int>> &matrix)
    {
        _matrix = &matrix;
        _total = matrix.size() * matrix[0].size();
        _starting_row = _row = 0;
        _starting_col = _col = 0;
        _index = 0;
    }
    SpiralIter(const SpiralIter &other) = default;
    int& operator*() const
    {
        return (*_matrix)[_row][_col];
    }
    SpiralIter& operator++()
    {
        if (*this == get_end(*_matrix)) {
            return *this;
        }
        if (++_index == _total) {
            *this = get_end(*_matrix);
            return *this;
        }
        if (_row == _starting_row && _col != (*_matrix)[0].size() - _starting_row - 1) {
            // We are on the top edge
            ++_col;
        } else if (_col == (*_matrix)[0].size() - _starting_row - 1 && _row != (*_matrix).size() - 1 - _starting_row) {
            ++_row;
        } else if (_row == (*_matrix).size() - 1 - _starting_row && _col != _starting_row) {
            // We are on the bottom edge
            --_col;
        } else if (_col == _starting_row && _row != _starting_row) {
            // We are on the left edge
            if (_row - 1 == _starting_row) {
                int tmp = _starting_col;
                _starting_row = _row;
                _starting_col = _col = tmp + 1;
            } else {
                --_row;
            }
        }
        return *this;
    }
    SpiralIter operator++(int)
    {
        SpiralIter ret = *this;
        this->operator++();
        return ret;
    }
    static const SpiralIter& get_end(vector<vector<int>> &matrix)
    {
        static SpiralIter end(matrix);
        end._row = -1;
        end._col = -1;
        return end;
    }
private:
    vector<vector<int>> *_matrix;
    int _row, _col;
    int _starting_row, _starting_col;
    int _total, _index;
};

bool operator==(const SpiralIter &m, const SpiralIter &n)
{
    return m._matrix == n._matrix && m._row == n._row && m._col == n._col;
}

bool operator!=(const SpiralIter &m, const SpiralIter &n)
{
    return !(m==n);
}

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) {
            return vector<int>();
        }
        
        SpiralIter p(matrix);
        SpiralIter e = SpiralIter::get_end(matrix);
        vector<int> r;

        while (p != e) {
            r.push_back(*p);
            ++p;
        }

        return r;
    }
};

int main()
{
    
    vector<vector<int>> m = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    const auto r = Solution().spiralOrder(m);

    for (const auto &v : r) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}