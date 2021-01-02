
// DAY 1 (Check Array Formation Through Concatenation)==============================================================

bool canFormArray(vector<int> &arr, vector<vector<int>> &pieces)
{
    vector<int> indices(101, -1);
    for (int i = 0; i < arr.size(); i++)
        indices[arr[i]] = i;

    for (int i = 0; i < pieces.size(); i++)
        for (int j = 0; j < pieces[i].size(); j++)
            if (indices[pieces[i][j]] == -1)
                return false;

    for (vector<int> v : pieces)
    {
        int i = indices[v[0]];
        for (int x : v)
        {
            if (i != indices[x])
                return false;
            i++;
        }
    }
    return true;
}

// DAY 2 (Find a Corresponding Node of a Binary Tree in a Clone of That Tree)===========================================================

TreeNode *getTargetCopy(TreeNode *original, TreeNode *cloned, TreeNode *target)
{
    if (!cloned)
        return nullptr;
    if (cloned->val == target->val)
        return cloned;
    TreeNode *left = getTargetCopy(original, cloned->left, target);
    if (left)
        return left;
    TreeNode *right = getTargetCopy(original, cloned->right, target);
    if (right)
        return right;

    return nullptr;
}