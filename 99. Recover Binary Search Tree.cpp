
// APPROACH 1 (Recursively) --> Time - O(n), Space - O(height of tree) [stack space]

TreeNode *prev = new TreeNode(INT_MIN), *node1 = nullptr, *node2 = nullptr;
void checkswap(TreeNode *curr)
{
    if (!curr)
        return;

    checkswap(curr->left);

    if (!node1 && curr->val < prev->val)
    {
        node1 = prev;
        node2 = curr;
    }
    else if (curr->val < prev->val)
        node2 = curr;

    prev = curr;
    checkswap(curr->right);
}

void recoverTree(TreeNode *root)
{
    TreeNode *curr = root;

    checkswap(root);

    if (node1 && node2)
        swap(node1->val, node2->val);
}

// APPROACH 2 (Iterative Approach)(Morris Inorder Traversal) --> Time - O(n), Space - O(1)

TreeNode *prev = new TreeNode(INT_MIN), *node1 = nullptr, *node2 = nullptr;

void checkSwap(TreeNode *root)
{
    if (!node1 && root->val < prev->val)
    {
        node1 = prev;
        node2 = root;
    }
    else if (root->val < prev->val)
        node2 = root;
}

void recoverTree(TreeNode *root)
{
    while (root)
    {
        TreeNode *rootp1 = root->left;

        if (!rootp1)
        {
            // cout<<root->val<<", ";
            checkSwap(root);
            prev = root;
            root = root->right;
            continue;
        }

        while (rootp1->right && rootp1->right != root)
            rootp1 = rootp1->right;

        if (rootp1->right == nullptr)
        {
            rootp1->right = root;
            root = root->left;
        }

        else if (rootp1->right == root)
        {
            // cout<<root->val<<", ";
            checkSwap(root);
            prev = root;
            root = root->right;
            rootp1->right = nullptr;
        }
    }
    // cout<<endl;
    if (node1 && node2)
        swap(node1->val, node2->val);
}