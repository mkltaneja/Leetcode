
ListNode *curr;
TreeNode *construct(int n)
{
    if (n == 0)
        return nullptr;

    TreeNode *l = construct(n / 2);

    TreeNode *root = new TreeNode(curr->val);
    curr = curr->next;
    root->left = l;

    root->right = construct((n - 1) / 2);

    return root;
}

TreeNode *sortedListToBST(ListNode *head)
{
    curr = head;
    ListNode *itr = head;
    int cnt = 0;
    while (itr)
    {
        itr = itr->next;
        cnt++;
    }
    return construct(cnt);
}