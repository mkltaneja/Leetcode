
// APPROACH 1 (Memoized)

int partition(int i, int n, int d, vector<int> &jd, vector<vector<int>> &dp)
{
    if (!d && (i == n - 1))
        return 0;
    if ((d && (i == n - 1)) || (!d && i < n - 1))
        return INT_MAX;
    if (i != -1 && dp[i + 1][d] != -1)
        return dp[i + 1][d];

    int mx = -1;
    int ans = INT_MAX;
    for (int j = i + 1; j < n; j++)
    {
        mx = max(mx, jd[j]);
        int ret = partition(j, n, d - 1, jd, dp);
        ret = (ret == INT_MAX) ? INT_MAX : ret + mx;
        ans = min(ans, ret);
    }
    return dp[i + 1][d] = ans;
}

int minDifficulty(vector<int> &jd, int d)
{
    int n = jd.size();
    if (n < d)
        return -1;

    vector<vector<int>> dp(n, vector<int>(d + 1, -1));
    int ans = partition(-1, n, d, jd, dp);

    return ans == INT_MAX ? -1 : ans;
}