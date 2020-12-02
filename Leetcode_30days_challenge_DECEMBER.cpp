// DAY 1 ()==============================================================

// METHOD 1 (void type)
void maxdepth(TreeNode* node, int depth, int &maxans)
{
    if(node == nullptr)
        return;
    maxans = max(maxans, depth);
    maxdepth(node->left, depth+1, maxans);
    maxdepth(node->right, depth+1, maxans);
}

int maxDepth(TreeNode* root) 
{
    int depth = 0;
    maxdepth(root, 1, depth);
    return depth;
}