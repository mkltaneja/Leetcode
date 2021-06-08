
// THIS IS THE OPTIMIZED ALGORITHM OF COUNTING THE NODES (Only correct for Complete Binary Tree)
// O(h^2) or O((logn)^2) [As height of complete binary tree is log(n)]
// [As starting from the root, we count the number of nodes in the left and right (which is O(h) operation) if they are equal, then we just return the answer (2^h - 1)nodes[Mathematically]; but if the left height and right height are unequal (where maximum difference can be 1 because of complete binary tree), then we ask the answer from its left and right recursively]
int getHeight_left(TreeNode *node)
{
    if (!node)
        return 0;
    return getHeight_left(node->left) + 1;
}

int getHeight_right(TreeNode *node)
{
    if (!node)
        return 0;
    return getHeight_right(node->right) + 1;
}

int countNodes(TreeNode *root)
{
    if (!root)
        return 0;

    int lefth = getHeight_left(root);
    int righth = getHeight_right(root);

    if (lefth == righth)
        return (1 << lefth) - 1;

    else
    {
        int leftcnt = countNodes(root->left);
        int rightcnt = countNodes(root->right);
        return leftcnt + rightcnt + 1;
    }
}