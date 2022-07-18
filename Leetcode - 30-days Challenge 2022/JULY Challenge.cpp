//  DAY 1 (1710. Maximum Units on a Truck)========================================================================================================

int maximumUnits(vector<vector<int>> &boxTypes, int truckSize)
{
    sort(boxTypes.begin(), boxTypes.end(), [](auto const &a, auto const &b)
         { return a[1] > b[1]; });
    int ans = 0;
    for (vector<int> v : boxTypes)
    {
        ans += min(truckSize, v[0]) * v[1];
        truckSize -= min(truckSize, v[0]);
    }
    return ans;
}

//  DAY 2 (1465. Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts)========================================================================================================

int maxArea(int h, int w, vector<int> &horizontalCuts, vector<int> &verticalCuts)
{
    horizontalCuts.insert(horizontalCuts.begin(), 0);
    horizontalCuts.push_back(h);
    verticalCuts.insert(verticalCuts.begin(), 0);
    verticalCuts.push_back(w);
    sort(horizontalCuts.begin(), horizontalCuts.end());
    sort(verticalCuts.begin(), verticalCuts.end());
    int mxw = 0, mxh = 0;
    for (int i = 0; i < horizontalCuts.size() - 1; i++)
        mxh = max(mxh, horizontalCuts[i + 1] - horizontalCuts[i]);
    for (int i = 0; i < verticalCuts.size() - 1; i++)
        mxw = max(mxw, verticalCuts[i + 1] - verticalCuts[i]);

    return (long)mxh * mxw % 1000000007;
}

//  DAY 3 (376. Wiggle Subsequence)========================================================================================================

int wiggleMaxLength(vector<int> &nums)
{
    int n = nums.size();
    int ans = 1, i = 1;

    while (i < n && nums[i] == nums[0])
        i++;
    if (i == n)
        return ans;

    int up = nums[i] > nums[0];
    while (i < n)
    {
        while (up && i < n && nums[i] >= nums[i - 1])
            i++;
        while (!up && i < n && nums[i] <= nums[i - 1])
            i++;
        up ^= 1;
        ans++;
    }

    return ans;
}

//  DAY 4 (135. Candy)========================================================================================================

// APPROACH 1 --> O(n*logn)

int candy(vector<int> &ratings)
{
    int n = ratings.size();
    vector<pair<int, int>> ri(n);
    for (int i = 0; i < n; i++)
        ri[i] = {ratings[i], i};

    sort(ri.begin(), ri.end());
    vector<int> candies(n);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int j = ri[i].second;
        int lans = (j && ratings[j - 1] < ratings[j]) ? candies[j - 1] + 1 : 1;
        int rans = (j + 1 < n && ratings[j + 1] < ratings[j]) ? candies[j + 1] + 1 : 1;
        candies[j] = max(lans, rans);
        ans += candies[j];
    }

    return ans;
}

// APPROACH 2 --> O(n)

int candy(vector<int> &ratings)
{
    int n = ratings.size();
    int ans = 0;

    vector<int> candies(n, 1);
    for (int i = 1; i < n; i++)
        if (ratings[i] > ratings[i - 1])
            candies[i] = candies[i - 1] + 1;
    for (int i = n - 2; i >= 0; i--)
        if (ratings[i] > ratings[i + 1])
            candies[i] = max(candies[i], candies[i + 1] + 1);
    for (int i = 0; i < n; i++)
        ans += candies[i];

    return ans;
}

// DAY 5 (128. Longest Consecutive Sequence)====================================================================================

int longestConsecutive(vector<int> &nums)
{
    unordered_map<int, int> mp;
    for (int x : nums)
    {
        if (mp.count(x))
            continue;
        mp[x] = 1;
        if (!mp.count(x - 1) && !mp.count(x + 1))
            continue;
        if (mp.count(x - 1) && mp.count(x + 1))
        {
            int lcnt = mp[x - (mp[x - 1])];
            int rcnt = mp[x + (mp[x + 1])];
            mp[x - (mp[x - 1])] = lcnt + rcnt + 1;
            mp[x + (mp[x + 1])] = lcnt + rcnt + 1;
        }
        else
        {
            if (mp.count(x - 1))
                mp[x] = ++mp[x - mp[x - 1]];
            else if (mp.count(x + 1))
                mp[x] = ++mp[x + (mp[x + 1])];
        }
    }

    int ans = 0;
    for (auto p : mp)
        ans = max(ans, p.second);

    return ans;
}

// DAY 6 (509. Fibonacci Number)===================================================================================================

int fib(int n)
{
    if (n <= 1)
        return n;
    int a = 0, b = 1, ans = 1;
    for (int i = 2; i <= n; i++)
    {
        ans = a + b;
        a = b;
        b = ans;
    }
    return ans;
}

// DAY 7 (97. Interleaving String)=============================================================================================

// APPROACH 1 (Usin 2D DP)

bool dfs(int i, int j, int k, int n, int m, int nm, string &s1, string &s2, string &s3, vector<vector<int>> &dp)
{
    if (i == n && j == m && k == nm)
        return true;
    if (k == nm)
        return false;
    if (dp[i][j] != -1)
        return dp[i][j];

    bool ans = false;
    if (i < n && s1[i] == s3[k])
        ans |= dfs(i + 1, j, k + 1, n, m, nm, s1, s2, s3, dp);
    if (j < m && s2[j] == s3[k])
        ans |= dfs(i, j + 1, k + 1, n, m, nm, s1, s2, s3, dp);

    return dp[i][j] = ans;
}

bool isInterleave(string s1, string s2, string s3)
{
    int n = s1.size(), m = s2.size(), nm = s3.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return dfs(0, 0, 0, n, m, nm, s1, s2, s3, dp);
}

// DAY 8 (1473. Paint House III)===================================================================================================

int dfs(int i, int nbr, int lastc, int m, int n, vector<vector<int>> &cost, vector<int> &houses, int target, vector<vector<vector<int>>> &dp)
{
    if (nbr > target)
        return -1;
    if (i == m)
    {
        if (nbr == target)
            return 0;
        return -1;
    }
    if (dp[i][nbr][lastc] != INT_MAX)
        return dp[i][nbr][lastc];

    if (houses[i])
    {
        if (houses[i] == lastc)
            return dp[i][nbr][lastc] = dfs(i + 1, nbr, houses[i], m, n, cost, houses, target, dp);
        else
            return dp[i][nbr][lastc] = dfs(i + 1, nbr + 1, houses[i], m, n, cost, houses, target, dp);
    }
    else
    {
        int ans = INT_MAX;
        for (int j = 0; j < n; j++)
        {
            int curr = 0;
            if (j + 1 == lastc)
                curr = dfs(i + 1, nbr, j + 1, m, n, cost, houses, target, dp);
            else
                curr = dfs(i + 1, nbr + 1, j + 1, m, n, cost, houses, target, dp);
            if (curr == -1)
                continue;
            ans = min(ans, curr + cost[i][j]);
        }
        return dp[i][nbr][lastc] = ans == INT_MAX ? -1 : ans;
    }
}

int minCost(vector<int> &houses, vector<vector<int>> &cost, int m, int n, int target)
{
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(target + 1, vector<int>(n + 1, INT_MAX)));
    return dfs(0, 0, 0, m, n, cost, houses, target, dp);
}

// DAY 9 (1696. Jump Game VI)================================================================================================

int maxResult(vector<int> &nums, int k)
{
    int n = nums.size();
    priority_queue<pair<int, int>> pq;
    pq.push({nums[n - 1], n - 1});
    for (int i = n - 2; i >= 0; i--)
    {
        while (pq.top().second > i + k)
            pq.pop();
        nums[i] += pq.top().first;
        pq.push({nums[i], i});
    }
    return nums[0];
}

// DAY 10 (746. Min Cost Climbing Stairs)============================================================================================

int minCostClimbingStairs(vector<int> &cost)
{
    int n = cost.size();
    for (int i = n - 2; i >= 0; i--)
    {
        cost[i] += min(cost[i + 1], (i == n - 2 ? 0 : cost[i + 2]));
    }
    return min(cost[0], cost[1]);
}

// DAY 11 (199. Binary Tree Right Side View)============================================================================================

vector<int> rightSideView(TreeNode *root)
{
    if (!root)
        return {};

    queue<TreeNode *> que;
    que.push(root);

    vector<int> ans;
    while (!que.empty())
    {
        int sz = que.size();
        while (sz--)
        {
            TreeNode *node = que.front();
            que.pop();
            if (sz == 0)
                ans.push_back(node->val);
            if (node->left)
                que.push(node->left);
            if (node->right)
                que.push(node->right);
        }
    }
    return ans;
}

// DAY 12 (473. Matchsticks to Square)===============================================================================================

bool findsum(int i, int sides, int sum, int vis, int tar, vector<int> &matchsticks)
{
    if (sides == 3)
        return true;
    if (sum == tar)
        return findsum(0, sides + 1, 0, vis, tar, matchsticks);
    if (i == matchsticks.size())
        return false;

    for (int j = i; j < matchsticks.size(); j++)
    {
        if (!(vis & (1 << j)) && sum + matchsticks[j] <= tar)
        {
            vis ^= (1 << j);
            if (findsum(j + 1, sides, sum + matchsticks[j], vis, tar, matchsticks))
                return true;
            vis ^= (1 << j);
        }
    }

    return false;
}

bool makesquare(vector<int> &matchsticks)
{
    int sum = 0;
    for (int x : matchsticks)
        sum += x;
    if (sum % 4)
        return false;

    int vis = 0;
    return findsum(0, 0, 0, vis, sum / 4, matchsticks);
}

// DAY 13 (102. Binary Tree Level Order Traversal)=====================================================================================

vector<vector<int>> levelOrder(TreeNode *root)
{
    if (!root)
        return {};
    vector<vector<int>> ans;

    queue<TreeNode *> que;
    que.push(root);
    while (!que.empty())
    {
        int sz = que.size();
        vector<int> lvl;
        while (sz--)
        {
            TreeNode *node = que.front();
            lvl.push_back(node->val);
            que.pop();

            if (node->left)
                que.push(node->left);
            if (node->right)
                que.push(node->right);
        }
        ans.push_back(lvl);
    }

    return ans;
}

// DAY 14 (105. Construct Binary Tree from Preorder and Inorder Traversal)=============================================================================

TreeNode *constructTree(int &i, int l, int r, vector<int> &pre, vector<int> &in, unordered_map<int, int> &mpi)
{
    if (r < l)
        return nullptr;

    TreeNode *node = new TreeNode(pre[i]);
    int idx = mpi[pre[i++]];

    node->left = constructTree(i, l, idx - 1, pre, in, mpi);
    node->right = constructTree(i, idx + 1, r, pre, in, mpi);

    return node;
}

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
    int n = inorder.size();
    unordered_map<int, int> mpi;
    for (int i = 0; i < n; i++)
        mpi[inorder[i]] = i;

    int i = 0;
    return constructTree(i, 0, n - 1, preorder, inorder, mpi);
}

// DAY 15 (695. Max Area of Island)============================================================================================================================

int dfs(int i, int j, int n, int m, vector<vector<int>> &grid)
{
    if (i == -1 || j == -1 || i == n || j == m || grid[i][j] == 0)
        return 0;

    grid[i][j] = 0;
    return dfs(i + 1, j, n, m, grid) +
           dfs(i, j + 1, n, m, grid) +
           dfs(i - 1, j, n, m, grid) +
           dfs(i, j - 1, n, m, grid) + 1;
}

int maxAreaOfIsland(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();

    int maxarea = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j])
                maxarea = max(maxarea, dfs(i, j, n, m, grid));

    return maxarea;
}

// DAY 16 (576. Out of Boundary Paths)================================================================================================

int mod = 1e9 + 7;
int dfs(int i, int j, int n, int m, int M, vector<vector<vector<int>>> &dp)
{
    if (i == -1 || j == -1 || i == n || j == m)
        return 1;
    if (M == 0)
        return 0;
    if (dp[i][j][M] != -1)
        return dp[i][j][M];

    int u = dfs(i + 1, j, n, m, M - 1, dp);
    int r = dfs(i, j + 1, n, m, M - 1, dp);
    int d = dfs(i - 1, j, n, m, M - 1, dp);
    int l = dfs(i, j - 1, n, m, M - 1, dp);
    return dp[i][j][M] = ((u % mod + r % mod) % mod) + ((d % mod + l % mod) % mod) % mod;
}

int findPaths(int m, int n, int maxMove, int startRow, int startColumn)
{
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(maxMove + 1, -1)));
    return dfs(startRow, startColumn, m, n, maxMove, dp) % mod;
}

// DAY 18 (1074. Number of Submatrices That Sum to Target)============================================================================================

int numSubmatrixSumTarget(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size();
    int m = matrix[0].size();

    for (int i = 0; i < n; i++)
        for (int j = 1; j < m; j++)
            matrix[i][j] += matrix[i][j - 1];

    int ans = 0;
    for (int p = 0; p < m; p++)
    {
        for (int j = p; j < m; j++)
        {
            unordered_map<int, int> sums;
            sums[0] = 1;
            int sum = 0;
            for (int i = 0; i < n; i++)
            {
                sum += matrix[i][j] - (p ? matrix[i][p - 1] : 0);
                ans += sums[sum - target];
                sums[sum]++;
            }
        }
    }

    return ans;
}