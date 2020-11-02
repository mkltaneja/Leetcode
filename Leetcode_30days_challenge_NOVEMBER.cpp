
// $ DAY 1 (Convert Binary Number in a Linked List to Integer)========================================================
int getDecimalValue(ListNode *head)
{
    int ans = 0;
    ListNode *temp = head;
    while (temp)
    {
        ans = 2 * ans + temp->val;
        temp = temp->next;
    }
    return ans;
}