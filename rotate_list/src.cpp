/*
Given a linked list, rotate the list to the right by k places, where k is non-negative.

Example 1:

Input: 1->2->3->4->5->NULL, k = 2
Output: 4->5->1->2->3->NULL
Explanation:
rotate 1 steps to the right: 5->1->2->3->4->NULL
rotate 2 steps to the right: 4->5->1->2->3->NULL

Example 2:

Input: 0->1->2->NULL, k = 4
Output: 2->0->1->NULL
Explanation:
rotate 1 steps to the right: 2->0->1->NULL
rotate 2 steps to the right: 1->2->0->NULL
rotate 3 steps to the right: 0->1->2->NULL
rotate 4 steps to the right: 2->0->1->NULL
*/

/**
 * Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == NULL || head->next == NULL) {
            // emtpy list or list with length 1
            return head;
        }

        // Get the length of the list.
        int n = 1;
        ListNode *p = head;
        while (p->next != NULL) { p = p->next; ++n; }

        // Get the steps we should rotate
        k = k % n;

        // Define another pointer pprev, the distance
        // between pprev and p should be k, and p
        // should point to the last element.
        ListNode *pprev = head;
        p = head;
        for (int i = 0; i < k; i++) {
            p = p->next;
        }
        // Move the p and pprev until p points to the last
        // element
        while(p->next != NULL) { pprev = pprev->next; p = p->next; }

        // Insert the sublist from pprev->next before head.
        p->next = head;
        head = pprev->next;
        pprev->next = NULL;

        return head;
    }
};