
TreeNode *deleteNode(TreeNode *root, int key)
{
    if (!root)
        return root;
    if (root->val < key)
        root->right = deleteNode(root->right, key);
    else if (root->val > key)
        root->left = deleteNode(root->left, key);
    else
    {
        if (!root->left && !root->right)
            return nullptr;
        else if (!root->left)
            return root->right;
        else if (!root->right)
            return root->left;
        else
        {
            TreeNode *temp = root->left;
            while (temp->right)
                temp = temp->right;
            temp->right = root->right;
            return root->left;
        }
    }
    return root;
}