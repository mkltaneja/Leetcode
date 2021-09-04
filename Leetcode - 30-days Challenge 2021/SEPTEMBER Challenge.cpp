// DAY 1 (Array Nesting)=============================================================================

int arrayNesting(vector<int> &nums)
{
    int maxcycle = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        int size = 0, j = i;
        while (nums[j] != -1)
        {
            int nxt = nums[j];
            nums[j] = -1;
            j = nxt;
            size++;
        }
        maxcycle = max(maxcycle, size);
    }
    return maxcycle;
}

// DAY 2 (Unique Binary Search Trees 2)=========================================================================

vector<TreeNode *> makeTree(int st, int end, vector<vector<vector<TreeNode *>>> &dp)
{
    if (st > end)
        return {nullptr};
    if (st == end)
        return dp[st][end] = {new TreeNode(st)};
    if (!dp[st][end].empty())
        return dp[st][end];

    vector<TreeNode *> curr;
    for (int x = st; x <= end; x++)
    {
        vector<TreeNode *> left = makeTree(st, x - 1, dp);
        vector<TreeNode *> right = makeTree(x + 1, end, dp);
        for (TreeNode *l : left)
            for (TreeNode *r : right)
                curr.push_back(new TreeNode(x, l, r));
    }
    return dp[st][end] = curr;
}

vector<TreeNode *> generateTrees(int n)
{
    vector<vector<vector<TreeNode *>>> dp(n + 1, vector<vector<TreeNode *>>(n + 1));
    return makeTree(1, n, dp);
}

// DAY 4 (Sum of Distances in Tree)===========================================================================

vector<int> cnt, ans;
void dfs1(int u, int p, vector<vector<int>> &gp)
{
    for (int v : gp[u])
    {
        if (v != p)
        {
            dfs1(v, u, gp);
            cnt[u] += cnt[v];
            ans[u] += ans[v] + cnt[v];
        }
    }
}
void dfs2(int u, int p, vector<vector<int>> &gp)
{
    for (int v : gp[u])
    {
        if (v != p)
        {
            ans[v] = ans[u] - cnt[v] + (gp.size() - cnt[v]);
            dfs2(v, u, gp);
        }
    }
}

vector<int> sumOfDistancesInTree(int n, vector<vector<int>> &edges)
{
    vector<vector<int>> gp(n);
    for (auto e : edges)
    {
        gp[e[0]].push_back(e[1]);
        gp[e[1]].push_back(e[0]);
    }
    cnt.resize(n, 1), ans.resize(n, 0);
    dfs1(0, -1, gp);
    dfs2(0, -1, gp);

    return ans;
}