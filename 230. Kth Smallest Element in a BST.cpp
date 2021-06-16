
// Using Morris Inorder Traversal to save stack space
int kthSmallest(TreeNode *root, int k)
{
    int ans = -1;
    while (root)
    {
        TreeNode *rootp1 = root->left;
        if (!rootp1)
        {
            if (--k == 0)
                ans = root->val;
            root = root->right;
        }
        else
        {
            while (rootp1->right && rootp1->right != root)
                rootp1 = rootp1->right;

            if (rootp1->right == nullptr)
            {
                rootp1->right = root;
                root = root->left;
            }
            else
            {
                if (--k == 0)
                    ans = root->val;
                rootp1->right = nullptr;
                root = root->right;
            }
        }
    }
    return ans;
}