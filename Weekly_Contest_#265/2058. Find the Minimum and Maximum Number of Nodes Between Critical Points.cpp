
vector<int> nodesBetweenCriticalPoints(ListNode *head)
{
    int i = 0, p = -1, fi = -1;
    int mnd = INT_MAX, mxd = INT_MIN;
    ListNode *node = head->next, *prev = head;

    while (node->next)
    {
        if ((node->val > prev->val && node->val > node->next->val) || (node->val < prev->val && node->val < node->next->val))
        {
            if (p != -1)
            {
                mnd = min(mnd, i - p);
                mxd = max(mxd, i - fi);
            }
            else
                fi = i;
            p = i;
        }
        prev = node;
        node = node->next;
        i++;
    }

    if (mnd == INT_MAX)
        return {-1, -1};
    else
        return {mnd, mxd};
}