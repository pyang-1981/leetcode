#include <vector>

using namespace std;

/* Try to find the rotating point using a binary search scheme:
*  1. Find the middle element at position m.
*  2. If v[m] < v[end-1], set the right to m-1;
*  3. If v[m] > v[end-1] set the left to m+1
*  4. if v[m] > v[m+1] && v[m] > v[m-1], m is the rotating point.  
*
*  Then We can binary search [0, m] and [m+1, end) using the binary
*  search respectively to find the desired element. 
*/

int rotating_point(const vector<int> &nums)
{
    int i = 0, j = nums.size() -1;

    /* Special cases when the vector length is 1 */
    if (nums.size() == 1) {
        return 0;
    }

    while (i <= j) {
        int m = (i + j) / 2;
        // Special case: the first element is the largest element
        if (m - 1 < 0 && nums[m] > nums[m+1]) return m;
        // Special case: the first element is the smallest element
        if (m - 1 < 0 && nums[m] < nums[nums.size() - 1]) return nums.size() - 1;
        if (m - 1 < 0 && nums[m] < nums[m+1]) { i = m + 1; continue; }
        if (nums[m] > nums[m-1] && nums[m] > nums[m+1]) return m;
        if (nums[m] > nums[nums.size()-1]) { i = m + 1; continue; }
        if (nums[m] < nums[nums.size()-1]) { j = m - 1; continue; }
    }

    return -1;
}

int binary_search_inc(const vector<int> &nums, int i, int j, int target)
{
    while(i <= j) {
        int m = (i + j) / 2;
        if (nums[m] == target) return (int)m;
        if (nums[m] > target) j = m - 1;
        if (nums[m] < target) i = m + 1;
    }

    return -1;
}

int binary_search_dec(const vector<int> &nums, int i, int j, int target)
{
    while(i <= j) {
        int m = (i + j) / 2;
        if (nums[m] == target) return (int)m;
        if (nums[m] > target) i = m + 1;
        if (nums[m] < target) j = m - 1;
    }

    return -1;
}

int search(const vector<int> &nums, int target)
{
    int r = rotating_point(nums);
    int p = binary_search_inc(nums, 0, r, target);
    if (p != -1) return p;
    return binary_search_inc(nums, r + 1, nums.size() - 1, target);
}


