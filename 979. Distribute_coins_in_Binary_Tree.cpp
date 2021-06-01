
int ans;

int dfs(TreeNode *node)
{
    if (!node)
        return 0;
    int lans = dfs(node->left);
    int rans = dfs(node->right);
    ans += abs(lans) + abs(rans);
    return lans + rans + (node->val - 1);
}

int distributeCoins(TreeNode *root)
{
    ans = 0;
    dfs(root);
    return ans;
}