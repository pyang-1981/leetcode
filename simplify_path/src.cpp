/*
Given an absolute path for a file (Unix-style), simplify it. Or in other words, convert it to the canonical path.

In a UNIX-style file system, a period . refers to the current directory. Furthermore, a double period .. moves the directory up a level. For more information, see: Absolute path vs relative path in Linux/Unix

Note that the returned canonical path must always begin with a slash /, and there must be only a single slash / between two directory names. The last directory name (if it exists) must not end with a trailing /. Also, the canonical path must be the shortest string representing the absolute path.

 

Example 1:

Input: "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.

Example 2:

Input: "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.

Example 3:

Input: "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.

Example 4:

Input: "/a/./b/../../c/"
Output: "/c"

Example 5:

Input: "/a/../../b/../c//.//"
Output: "/c"

Example 6:

Input: "/a//b////c/d//././/.."
Output: "/a/b/c"
*/

#include <string>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        string simplified_path;
        auto it = path.begin();

        simplified_path.push_back(*it);
        ++it;
        while (it != path.end()) {
            if (*it == '/' && simplified_path.back() == '/') { ++it; continue; }; // Discard double //
            if (*it == '.') {
                if (path.end() - it >= 3 && *(it + 1) == '.' && *(it + 2) == '.') {
                    // Special case where ... is a valid filename.
                    it += 3;
                    simplified_path.append("...");
                    continue;
                }
                if ((it + 1) != path.end() && *(it + 1) == '.' &&
                    ((it + 2) == path.end() || *(it + 2) == '/')) {
                    // double .. followd by / or end of the string.
                    // plus it is not ...
                    it += 2; // skip ..
                    if (it != path.end() && *it == '/') ++it; // skip /
                    if (simplified_path == "/") continue; // cannot go up from the root
                    // Otherwise
                    simplified_path.pop_back(); // pop /
                    while (simplified_path.back() != '/') {
                        simplified_path.pop_back(); // Continue to pop until the prevouis /
                    }
                    continue;
                } else if (it + 1 == path.end() || *(it + 1) == '/') {
                    // single . followed by / or end of the string
                    // plus it is not ...
                    ++it; // skip .
                    if (it != path.end() && *it == '/') ++it; //skip /
                    continue;
                }
            }
            simplified_path.push_back(*it);
            ++it;
        }

        // Discard the trailing /
        while(simplified_path.back() == '/' && simplified_path.length() > 1) {
            simplified_path.pop_back();
        }

        return simplified_path;
    }
};


int main()
{
    Solution().simplifyPath("/...");
    return 0;
}