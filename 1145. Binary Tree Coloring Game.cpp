
int lc = 0, rc = 0;
int dfs(TreeNode *node, int x)
{
    if (!node)
        return 0;
    int l = dfs(node->left, x);
    int r = dfs(node->right, x);
    if (node->val == x)
    {
        lc = l;
        rc = r;
    }
    return l + r + 1;
}

bool btreeGameWinningMove(TreeNode *root, int n, int x)
{
    dfs(root, x);
    int pc = n - (lc + rc + 1);
    return (pc > n / 2 || lc > n / 2 || rc > n / 2);
}