#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/* We use a two dimensional array to hold the conversion.
 * The row number is specified as one of the input. For
 * simplicity, we set the column number to the size of the
 * original string (it is overprovisioned). The elements
 * in the array is initialized to 0 (invalid char) at the
 * beginning.
 * 
 * We use an index n to track the current position in the
 * string, and use a switch d to indicate the direction
 * we write the characters in the two dimensional array,
 * and use i and j to indicate the current position in the
 * array.Then we can fill the two dimensional array according to
 * these variables.
 * 
 * At the last step, we scan the array row by row, skipping
 * the 0 elements, and print out all the other elements
 * one by one.
 */

char **init_table(size_t n, int numRows)
{
    char **table;
    table = new char*[numRows];
    for (int i = 0; i < numRows; i++) {
        table[i] = new char[n];
        memset(table[i], 0, n);
    }

    return table;
}

void destroy_table(char **table, int numRows)
{
    for (int i = 0; i < numRows; i++) {
        delete[] table[i];
    }
    delete[] table;
}

enum class Direction {
    DOWN,
    DIAG_UP
};

string zigzag_conversion(const string &s, int numRows)
{
    if (numRows == 1) {
        return s;
    }

    char **table = init_table(s.size(), numRows);
    int n = 0;
    Direction d = Direction::DOWN;
    int i = 0, j = 0;

    for (int n = 0; n < s.size(); n++) {
        switch (d)
        {
        case Direction::DOWN:
            table[i++][j] = s[n];
            if (i == numRows) {
                i = i - 2;
                j = j + 1;
                d = Direction::DIAG_UP;
            }
            break;
        case Direction::DIAG_UP:
            table[i--][j++] = s[n];
            if (i == -1) {
                i = 1;
                d = Direction::DOWN;
            }
            break;
        }
    }

    string res(s.size(), 0);
    n = 0;
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < s.size(); j++) {
            if (table[i][j] != 0) {
                res[n++] = table[i][j];
            }
        }
    }

    destroy_table(table, numRows);
    return res;
}
