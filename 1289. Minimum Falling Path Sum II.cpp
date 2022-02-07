
int minFallingPathSum(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    int pmn = INT_MAX, pmn2 = INT_MAX, pmncnt = 0;
    int minans = INT_MAX;
    vector<vector<int>> dp(n, vector<int>(m));
    for (int i = n - 1; i >= 0; i--)
    {
        int mn = INT_MAX, mn2 = INT_MAX, mncnt = 0;
        for (int j = 0; j < m; j++)
        {
            if (i == n - 1)
                dp[i][j] = grid[i][j];
            else
            {
                int dans = ((dp[i + 1][j] != pmn) || (pmncnt > 1)) ? pmn : pmn2;
                dp[i][j] = grid[i][j] + dans;
            }

            if (i == 0)
                minans = min(minans, dp[i][j]);

            if (dp[i][j] < mn)
            {
                mn2 = mn;
                mn = dp[i][j];
                mncnt = 1;
            }
            else if (dp[i][j] == mn)
            {
                mn2 = mn;
                mncnt++;
            }
            else
                mn2 = min(mn2, dp[i][j]);
        }
        pmn = mn, pmn2 = mn2, pmncnt = mncnt;
    }
    return minans;
}