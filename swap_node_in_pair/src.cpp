
#include <cstdlib>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* swap_in_pair(ListNode *head)
{
    ListNode fake(0);
    ListNode *p, *f, *s;

    if (head == NULL || head->next == NULL) {
        return head;
    }

    fake.next = head;
    p = &fake, f = head, s = head->next;

    while(true) {
        p->next = s;
        f->next = s->next;
        s->next = f;

        p = f;
        f = f->next;
        if (f == NULL) break;
        s = f->next;
        if (s == NULL) break;
    }

    return fake.next;
}