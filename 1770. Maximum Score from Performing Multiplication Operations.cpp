
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