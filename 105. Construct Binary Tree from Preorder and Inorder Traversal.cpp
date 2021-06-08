
TreeNode *build(int l1, int r1, int l2, int r2, vector<int> &pre, unordered_map<int, int> &m)
{
    if (l1 > r1 || l2 > r2)
        return nullptr;
    if (l2 == r2)
        return new TreeNode(pre[l1], nullptr, nullptr);

    int i = m[pre[l1]];
    TreeNode *root = new TreeNode(pre[l1]);

    int count = (i - l2);

    root->left = build(l1 + 1, l1 + count, l2, i - 1, pre, m);
    root->right = build(l1 + count + 1, r1, i + 1, r2, pre, m);

    return root;
}

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
    unordered_map<int, int> m;
    for (int i = 0; i < inorder.size(); i++)
        m[inorder[i]] = i;
    TreeNode *root = build(0, preorder.size() - 1, 0, inorder.size() - 1, preorder, m);
    return root;
}