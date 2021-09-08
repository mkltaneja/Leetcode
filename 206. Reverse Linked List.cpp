
ListNode *reverseList(ListNode *head)
{
    ListNode *prev = nullptr, *curr = head, *forw = head;
    while (curr)
    {
        forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }
    return prev;
}