
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

// $ DAY 2 (Insertion Sort List)========================================================================

ListNode *insertionSortList(ListNode *head)
{
    ListNode *ans = new ListNode(INT_MIN);

    while (head)
    {
        ListNode *tmp = ans;
        while (tmp->next && tmp->next->val < head->val)
            tmp = tmp->next;

        ListNode *nextnode = head->next;
        head->next = tmp->next;
        tmp->next = head;
        head = nextnode;
    }

    return ans->next;
}

// $ DAY 4 (Consecutive Characters)============================================================

// METHOD 1 (Using Hashmap)
int maxPower(string s)
{
    unordered_map<char, int> m;
    int maxlen = 0, j = 0;

    for (int i = 0; i < s.size(); i++)
    {
        m[s[i]]++;
        while (m.size() > 1)
        {
            if (--m[s[j]] == 0)
                m.erase(s[j]);
            j++;
        }
        maxlen = max(maxlen, i - j + 1);
    }
    return maxlen;
}