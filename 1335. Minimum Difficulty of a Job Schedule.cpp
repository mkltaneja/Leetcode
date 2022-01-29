
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

// APPROACH 2 (Tabulated)

int minDifficulty(vector<int> &jd, int d)
{
    int n = jd.size();
    if (n < d)
        return -1;
    vector<vector<int>> dp(d + 1, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++)
        dp[1][i] = i ? max(dp[1][i - 1], jd[i]) : jd[i];

    for (int days = 2; days <= d; days++)
    {
        for (int i = days - 1; i < n; i++)
        {
            int mx = -1;
            for (int j = i; j >= days - 1; j--)
            {
                mx = max(mx, jd[j]);
                dp[days][i] = min(dp[days][i], dp[days - 1][j - 1] + mx);
            }
        }
    }
    return dp[d][n - 1];
}