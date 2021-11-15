/*
  Given an array of non-negative integers, you are initially positioned at the first index of the array.

  Each element in the array represents your maximum jump length at that position.

  Determine if you are able to reach the last index.

  Example 1:

  Input: [2,3,1,1,4]
  Output: true
  Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

  Example 2:

  Input: [3,2,1,0,4]
  Output: false
  Explanation: You will always arrive at index 3 no matter what. Its maximum
  jump length is 0, which makes it impossible to reach the last index.
*/


#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    bool canJump(const vector<int>& nums) {
	if (nums.size() == 0) {
	    return true;
	}

	if (nums.size() == 1) {
	    return true;
	}

	stack<pair<int,int>> st;
	for (int i = 1; i <= nums[0]; i++) {
	    st.push(make_pair(0, i));
	}

	while (!st.empty()) {
	    const auto ps = st.top();
	    st.pop();
	    int next = ps.first + ps.second;
	    cout << "Current pos=" << ps.first << " step=" << ps.second
		 << " next pos=" << next << endl;
	    cout << "nums size=" << nums.size() << endl;
	    if (next == nums.size() - 1) {
		return true;
	    }
	    if (next < nums.size() - 1) {
		for (int i = 1; i <= nums[next]; i++) {
		    cout << "Push next pos=" << next
			 << " next step=" << i << endl;
		    st.push(make_pair(next, i));
		} 
	    }
		cout << "stack size: " << st.size() << endl;
	}

	return false;
    }
};


int main()
{
    Solution s;
    cout << s.canJump({2,0,6,9,8,4,5,0,8,9,1,2,9,6,8,8,0,6,3,1,2,2,1,2,6,5,3,1,2,2,6,4,2,4,3,0,0,0,3,8,2,4,0,1,2,0,1,4,6,5,8,0,7,9,3,4,6,6,5,8,9,3,4,3,7,0,4,9,0,9,8,4,3,0,7,7,1,9,1,9,4,9,0,1,9,5,7,7,1,5,8,2,8,2,6,8,2,2,7,5,1,7,9,6}) << endl;
    return 0;
}
