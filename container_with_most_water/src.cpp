#include <algorithm>
#include <vector>

using namespace std;

/* Important note: we need to start with the container with
* the maximum width, that is the container |heights[0], heights[n - 1]|
*
* The area of this container is
*
* min(heights[0], heights[n-1]) * n -1
*
* Then we need to consider the containers with width n - 2.
* These containers should not have the smaller one of
* the heights[0] and heights[n-1] as the boundary, since
* it will only produce a container with a smaller area.
*
* Now we have reduced the width of the max container by 1.
* Following this pattern, we continue to consider the
* containers with width n - 3, n -4, etc. Then report the
* max container area among all of them.
*  
*/

int max_container_area(const vector<int> &heights)
{
    int i = 0, j = heights.size() - 1;
    int max = min(heights[i], heights[j]) * (j - i);
    
    if (heights[i] <= heights[j]) {
        i = i + 1;
    } else {
        j = j - 1;
    }

    while (i < j) {
        int temp = min(heights[i], heights[j]) * (j - i);
        if (temp >= max) {
            max = temp;
        }
        if (heights[i] <= heights[j]) {
            i = i + 1;
        } else {
            j = j - 1;
        }
    }

    return max;
}
