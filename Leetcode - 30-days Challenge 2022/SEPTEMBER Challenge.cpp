// DAY 1 (1448. Count Good Nodes in Binary Tree)===========================================================================

int dfs(TreeNode* node, int mx)
{
    if(!node) return 0;

    mx = max(mx, node->val);
    return dfs(node->left, mx) + dfs(node->right, mx) + (node->val >= mx);
}

int goodNodes(TreeNode* root) 
{
    return dfs(root, INT_MIN);
}
