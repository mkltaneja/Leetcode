
// DAY 1 (Palindrome Linked List)===============================================================

// METHOD 1 (Using Extra Space (Stack))
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

// METHOD 2 (Const Extra Space) -- (By reversing the lower half of LL)

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
    ListNode *curr = head, *prev = nullptr, *forw = head;

    while (i++ < n / 2)
    {
        tmp = tmp->next;
        forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }
    ListNode *tmp1 = prev;

    if (n & 1)
        tmp = tmp->next;
    while (tmp && tmp1)
    {
        // cout<<tmp->val<<" "<<tmp1->val;
        if (tmp->val != tmp1->val)
            return false;
        tmp = tmp->next;
        tmp1 = tmp1->next;
    }
    return (!tmp && !tmp1);
}