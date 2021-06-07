
int maxsum = INT_MIN;
int maxPathSum_(TreeNode *root)
{
    if (!root)
        return 0;

    int lsum = maxPathSum_(root->left);
    int rsum = maxPathSum_(root->right);

    int curvedsum = (lsum + rsum + root->val);
    int left_linearSum = (lsum + root->val);
    int right_linearSum = (rsum + root->val);
    maxsum = max({maxsum, curvedsum, left_linearSum, right_linearSum, root->val});

    return max({left_linearSum, right_linearSum, root->val});
}

int maxPathSum(TreeNode *root)
{
    maxPathSum_(root);
    return maxsum;
}