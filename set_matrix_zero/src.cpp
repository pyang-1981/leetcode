/*
Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.

Example 1:

Input: 
[
  [1,1,1],
  [1,0,1],
  [1,1,1]
]
Output: 
[
  [1,0,1],
  [0,0,0],
  [1,0,1]
]

Example 2:

Input: 
[
  [0,1,2,0],
  [3,4,5,2],
  [1,3,1,5]
]
Output: 
[
  [0,0,0,0],
  [0,4,5,0],
  [0,3,1,0]
]

Follow up:

    A straight forward solution using O(mn) space is probably a bad idea.
    A simple improvement uses O(m + n) space, but still not the best solution.
    Could you devise a constant space solution?
*/


#include <vector>

using namespace std;

/*
*  For the submatrix that does not include the first col and row,
*  if a element == 0, we set the elements in the first col and row
*  to 0.
*
*  Then we can zerio the submatrix according to the elements
*  in the first col and row.
*
*  Then we zero the first col and first row separately.
*/

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        
        // Since we are using the first row and first col
        // to mark, we need to remember whether the
        // the first row and col should zeroed or not.
        bool zero_first_row = false;
        bool zero_first_col = false;
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[i][0] == 0) {
                zero_first_col = true;
                break;
            }
        }
        for (int i = 0; i < matrix[0].size(); i++) {
            if (matrix[0][i] == 0) {
                zero_first_row = true;
                break;
            }
        }

        // Check the elements in the matrix except
        // the first row and first col.
        for (int i = 1; i < matrix.size(); ++i) {
            for (int j = 1; j < matrix[0].size(); ++j) {
                if(matrix[i][j] == 0) {
                    // If the element is 0,
                    // set the first element in its row to 0.
                    matrix[i][0] = 0;
                    // Set the first element in its col to 0.
                    matrix[0][j] = 0;
                }
            }
        }

        // Check the first element in each col,
        // if it is 0, zero the corresponding col,
        // except the first elment.
        for(int i = 1; i < matrix[0].size(); i++) {
            if (matrix[0][i] == 0) {
                for (int j = 1; j < matrix.size(); j++) {
                    matrix[j][i] = 0;
                }
            }
        }

        // Check the first element in each row,
        // if it is 0, zero the corresponding row,
        // except the first element. 
        for (int i = 1; i < matrix.size(); i++) {    
            if (matrix[i][0] == 0) {
                for (int j = 1; j < matrix[0].size(); j++) {
                    matrix[i][j] = 0;
                }
            }
        }

        // Zero the first col if it is necessary.
        if (zero_first_col) {
            for (int i = 0; i < matrix.size(); i++) {
                matrix[i][0] = 0;
            }
        }

        // Zero the first row if it is necessary.
        if (zero_first_row) {
            for (int i = 0; i < matrix[0].size(); i++) {
                matrix[0][i] = 0;
            }
        }
    }
};

int main()
{
    vector<vector<int>> matrix = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    Solution().setZeroes(matrix);
    return 0;
}