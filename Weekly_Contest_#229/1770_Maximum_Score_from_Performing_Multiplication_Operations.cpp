
int dfs(int i, int j, int k, int m, vector<int> &a, vector<int> &b, vector<vector<int>> &dp)
{
    if (k == m)
        return 0;
    if (dp[i][k] != INT_MIN)
        return dp[i][k];
    dp[i][k] = max(a[i] * b[k] + dfs(i + 1, j, k + 1, m, a, b, dp), a[j] * b[k] + dfs(i, j - 1, k + 1, m, a, b, dp));

    return dp[i][k];
}

int maximumScore(vector<int> &a, vector<int> &b)
{
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(m, vector<int>(m, INT_MIN));
    return dfs(0, n - 1, 0, m, a, b, dp);
}