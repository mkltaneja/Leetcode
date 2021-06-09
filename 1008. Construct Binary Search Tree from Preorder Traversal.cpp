
TreeNode *buildBST(int &i, vector<int> &preorder, int mn, int mx)
{
    if (i == preorder.size())
        return nullptr;
    if (preorder[i] <= mn || preorder[i] >= mx)
        return nullptr;

    TreeNode *root = new TreeNode(preorder[i++]);

    root->left = buildBST(i, preorder, mn, root->val);
    root->right = buildBST(i, preorder, root->val, mx);

    return root;
}

TreeNode *bstFromPreorder(vector<int> &preorder)
{
    int i = 0;
    return buildBST(i, preorder, INT_MIN, INT_MAX);
}