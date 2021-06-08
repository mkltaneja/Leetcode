
double mindiff = INT_MAX;
int ans = -1;
void findans(TreeNode *root, double target)
{
    if (!root)
        return;
    if (abs(root->val - target) < mindiff)
    {
        mindiff = abs(root->val - target);
        ans = root->val;
    }
    if (root->val < target)
        closestValue(root->right, target);
    else
        closestValue(root->left, target);
}

int closestValue(TreeNode *root, double target)
{
    findans(root, target);
    return ans;
}