
TreeNode *ans = nullptr;
void dfs(TreeNode *node, TreeNode *p)
{
    if (!node)
        return;
    if (node->val > p->val)
    {
        ans = node;
        dfs(node->left, p);
    }
    else
        dfs(node->right, p);
}

TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p)
{
    dfs(root, p);
    return ans;
}