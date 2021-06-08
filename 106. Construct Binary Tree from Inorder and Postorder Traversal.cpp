
TreeNode *build(int l1, int r1, int l2, int r2, vector<int> &postorder, unordered_map<int, int> &m)
{
    if (l1 > r1)
        return nullptr;
    if (l1 == r1)
        return new TreeNode(postorder[r1]);
    int i = m[postorder[r1]];
    TreeNode *root = new TreeNode(postorder[r1]);

    int count = (r2 - i);

    root->left = build(l1, r1 - count - 1, l2, i - 1, postorder, m);
    root->right = build(r1 - count, r1 - 1, i + 1, r2, postorder, m);

    return root;
}

TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
{
    unordered_map<int, int> m;
    for (int i = 0; i < inorder.size(); i++)
        m[inorder[i]] = i;
    return build(0, postorder.size() - 1, 0, inorder.size() - 1, postorder, m);
}