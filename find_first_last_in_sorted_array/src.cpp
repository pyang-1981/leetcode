/*
Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].
*/

#include<vector>

using namespace std;

int binary_search(const vector<int> &nums, int target)
{
    int i = 0, j = nums.size() - 1;

    while(i <= j) {
        int m = (i + j) / 2;
        if (target == nums[m]) return m;
        if (target > nums[m]) i = m + 1;
        if (target < nums[m]) j = m - 1;
    }

    return -1;
}

vector<int> search(const vector<int> &nums, int target)
{
    int r = binary_search(nums, target);
    if (r == -1) {
        return {-1, -1};
    }

    vector<int> res;
    for (int i = r; i >= 0; i--) {
        if (nums[i] != target) {
            res.push_back(i + 1);
        }
    }
    for (int i = r; i < nums.size(); i++) {
        if(nums[i] != target) {
            res.push_back(i - 1);
        }
    }

    return res;
}