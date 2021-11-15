#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;

/*
* Scan the vector from right to left while the increasing
* pattern holds. Once find the element a that is smaller
* than the previous element, stop scanning.
*
* Find the element b that is closet-greater than a, on the
* the right hand side of a, swap a and b, then sort the elements
* on the right hand side of b, the resulting vector is
* the next permutation.
*
* Special cases:
* (1) We can not find such a element a. Then we are at the end
*     of the permutation, start from the beginning, i.e.,
*     reverse the whole vector.
*
* Improvements:
* (1) We can use binary search to find the element b.
* (2) 
*/


/*
* nums[i] to nums[j] is in the decreasing order
*/
int bin_search(vector<int> nums, size_t i, size_t j, int a)
{
    if (i == j) {
        return i; // nums[i] is b.
    }

    while (i < j) {
        int m = (i + j) / 2; // floor points to the larger element.
        if (nums[m] == a) {
            j = m - 1;  // Try to find b > a strictly.
        } else if (nums[m] < a) {
            j = m - 1;
        } else {
            //nums[m] > a
            i = m + 1;
            if (nums[i] <= a) {
                return m;
            }
        }
    }

    if ( j < i ) return -1; // No such b.
    if (nums[i] <= a) return i - 1;
    return i;
}

void next_perm(vector<int> &num)
{
    /* Scan the vector from right to left
    */
   size_t i;
   for (i = num.size() - 1; i >= 1; i--) {
       if (num[i] > num[i-1]) {
           break;
       }
   }

   if (i == 0) {
       // We are at the end of the permutation.
       reverse(num.begin(), num.end());
       return;
   }

   // Now num[i - 1] is a
   int b_pos = bin_search(num, i, num.size() - 1, num[i-1]);
   // b_pos cannot be -1, we already handled this case in
   // the first if branch.
   swap(num[i-1], num[b_pos]);
   // Reverse the elemnts from i to the end.
   reverse(num.begin() + i, num.end());
}


int main()
{
    int input;
    vector<int> v;

    while (cin >> input) {
        v.push_back(input);
    }

    cout << "------" << endl;

    next_perm(v);

    for (auto e : v) {
        cout << e << " ";
    }
    cout << endl;

    return 0;
}


