
// DAY 1 (Palindrome Linked List)===============================================================

// APPROACH 1 (Using Extra Space (Stack))
bool isPalindrome(ListNode *head)
{
    int n = 0;
    ListNode *itr = head;
    while (itr)
    {
        n++;
        itr = itr->next;
    }
    int i = 0;
    ListNode *tmp = head;
    stack<int> st;
    while (i++ < n / 2)
    {
        st.push(tmp->val);
        tmp = tmp->next;
    }

    if (n & 1)
        tmp = tmp->next;
    while (tmp && !st.empty())
    {
        if (tmp->val != st.top())
            return false;
        tmp = tmp->next;
        st.pop();
    }
    return (st.empty() && !tmp);
}