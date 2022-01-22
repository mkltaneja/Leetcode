
int dfs(int i, int m, int n, vector<int> &psum, vector<vector<int>> &dp)
{
    if (2 * m >= n - i)
        return psum[i];

    if (dp[i][m] != -1)
        return dp[i][m];

    int minans = INT_MAX;
    for (int x = 1; x <= 2 * m; x++)
        minans = min(minans, dfs(i + x, max(m, x), n, psum, dp));

    return dp[i][m] = psum[i] - minans;
}

int stoneGameII(vector<int> &piles)
{
    int n = piles.size();
    vector<int> psum(n, 0);
    for (int i = n - 1; i >= 0; i--)
        psum[i] = piles[i] + (i < (n - 1) ? psum[i + 1] : 0);
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return dfs(0, 1, n, psum, dp);
}