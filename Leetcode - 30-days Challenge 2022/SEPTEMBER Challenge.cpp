// DAY 1 (1448. Count Good Nodes in Binary Tree)===========================================================================

int dfs(TreeNode* node, int mx)
{
    if(!node) return 0;

    mx = max(mx, node->val);
    return dfs(node->left, mx) + dfs(node->right, mx) + (node->val >= mx);
}

int goodNodes(TreeNode* root) 
{
    return dfs(root, INT_MIN);
}

// DAY 2 (637. Average of Levels in Binary Tree)=======================================================================

vector<double> averageOfLevels(TreeNode* root) 
{
    vector<double> ans;
    queue<TreeNode*> que;
    que.push(root);

    while(!que.empty())
    {
        int sz = que.size();
        double sum = 0, tot = 0;
        while(sz--)
        {
            TreeNode* node = que.front();
            que.pop();
            sum += node->val;
            tot++;
            if(node->left)
                que.push(node->left);
            if(node->right)
                que.push(node->right);
        }
        ans.push_back(sum/tot);
    }

    return ans;
}

// DAY 3 (967. Numbers With Same Consecutive Differences)============================================================================

vector<int> ans;
void dfs(int x, int n, int k)
{
    if(n == 0)
    {
        ans.push_back(x);
        return;
    }

    if(x%10 - k >= 0)
        dfs(x*10 + (x%10 - k), n-1, k);
    if(k && x%10 + k <= 9)
        dfs(x*10 + (x%10 + k), n-1, k);
}

vector<int> numsSameConsecDiff(int n, int k) 
{
    for(int x = 1; x <= 9; x++)
        dfs(x, n-1, k);
    return ans;
}
