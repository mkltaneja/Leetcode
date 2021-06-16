
TreeNode *flat(TreeNode *node)
{
    if (!node || (!node->left && !node->right))
        return node;

    TreeNode *ltail = flat(node->left);
    TreeNode *rtail = flat(node->right);

    if (!ltail)
        return rtail;

    TreeNode *rnode = (node->right) ? rtail : ltail;
    ltail->right = node->right;
    node->right = node->left;
    node->left = nullptr;
    return rnode;
}

void flatten(TreeNode *root)
{
    flat(root);
}