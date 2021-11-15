#include <cstdlib>

using namespace std;

/* Keep three pointers, first, second, and prev.
* The distance between first and second is set to n
* initially, then we move first and second one step
* and a time. If second == NULL (end), then the first
* points to the to-be-deleted node. Also we keep prev
* pointing to the node just before first (for deletion).
*/

struct ListNode {       
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* RmNthNodeFromEnd(ListNode *head, int n)
{
    ListNode *first = head, *second = head, *prev = head;

    // Advance second forward n steps
    for (int i = 0; i < n; i++) {
        if (second == NULL && i < n) {
            return head;
        }
        second = second->next;
    }

    // Advance first and second one step at a time,
    // until second == NULL. At this time first points
    // to the to-be-deleted node.
    // We also move prev so that it points to the node
    // just before first.
    while (second != NULL) {
        second = second->next;
        if (prev != first) {
            prev = prev->next;
        }
        first = first->next;
    }

    // Now if first == prev, the above while loop
    // is not executed. In this case, the head of the
    // list need to be deleted.
    if (first == prev) {
        ListNode *tmp = head->next;
        delete head;
        return tmp;
    } else {
        // delete first
        prev->next = first->next;
        delete first;
        return head;
    }
}

