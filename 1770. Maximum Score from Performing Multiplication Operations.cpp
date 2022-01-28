
// APPROACH 1 (Memoization)

int dfs(int i, int k, int n, int m, vector<int> &nums, vector<int> &mult, vector<vector<int>> &dp)
{
    if (k == m)
        return 0;
    if (dp[i][k] != -1)
        return dp[i][k];
    int j = (n - 1) - (k - i);

    return dp[i][k] = max(nums[i] * mult[k] + dfs(i + 1, k + 1, n, m, nums, mult, dp),
                          nums[j] * mult[k] + dfs(i, k + 1, n, m, nums, mult, dp));
}

int maximumScore(vector<int> &nums, vector<int> &multipliers)
{
    int n = nums.size(), m = multipliers.size();
    vector<vector<int>> dp(m, vector<int>(m, -1));
    return dfs(0, 0, n, m, nums, multipliers, dp);
}

// APPROACH 2 (Tabulated)

int maximumScore(vector<int> &nums, vector<int> &multipliers)
{
    int n = nums.size(), m = multipliers.size();
    vector<vector<int>> dp(m + 1, vector<int>(m + 1, 0));
    for (int k = m - 1; k >= 0; k--)
    {
        int x = multipliers[k];
        for (int i = k; i >= 0; i--)
        {
            int j = (n - 1) - (k - i);
            dp[i][k] = max(x * nums[i] + dp[i + 1][k + 1], x * nums[j] + dp[i][k + 1]);
        }
    }
    return dp[0][0];
}