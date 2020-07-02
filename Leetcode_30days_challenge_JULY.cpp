// DAY 1 (Arranging coins)=======================================

// Brute force
// O(sqrt(n))
int arrangeCoins(int n)
{
    int i = 1, count = 0;
    while ((n - i) >= 0)
    {
        count++;
        n -= i;
        i++;
    }
    return count;
}

// O(logn)
int arrangeCoins(int n)
{
    int si = 0, ei = n;
    while (si <= ei)
    {
        long int mid = si + (ei - si) / 2;
        if ((mid * (mid + 1)) / 2 == n)
            return mid;
        else if ((mid * (mid + 1)) / 2 < n)
            si = mid + 1;
        else
            ei = mid - 1;
    }
    return ei;
}

///////////////////OR////////////////////\

// O(1)
int arrangeCoins(int n)
{
    return (int)(-0.5 + sqrt(0.25 + (long int)2 * n));
}

// DAY 2 (Binary Tree Level Order Traversal 2)====================================================================

// BFS
vector<vector<int>> levelOrderBottom(TreeNode *root)
{
    if (root == nullptr)
        return {};
    queue<TreeNode *> que;
    que.push(root);
    vector<vector<int>> ans;
    ans.push_back({root->val});
    while (!que.empty())
    {
        vector<int> level;
        int size = que.size();
        while (size--)
        {
            TreeNode *top = que.front();
            que.pop();
            TreeNode *l = top->left;
            TreeNode *r = top->right;
            if (l)
            {
                que.push(l);
                level.push_back(l->val);
            }
            if (r)
            {
                que.push(r);
                level.push_back(r->val);
            }
        }
        if (level.size())
            ans.push_back(level);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}