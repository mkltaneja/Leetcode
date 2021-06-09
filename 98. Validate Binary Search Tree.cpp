
bool isValidBST_(TreeNode *node, long mn, long mx)
{
    if (!node)
        return true;
    if (node->val <= mn || node->val >= mx)
        return false;
    bool lans = isValidBST_(node->left, mn, node->val);
    bool rans = isValidBST_(node->right, node->val, mx);

    return (lans && rans);
}

bool isValidBST(TreeNode *root)
{
    long mn = LONG_MIN, mx = LONG_MAX;
    return isValidBST_(root, mn, mx);
}