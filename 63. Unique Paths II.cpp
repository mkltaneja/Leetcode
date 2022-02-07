
int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
{
    int n = obstacleGrid.size(), m = obstacleGrid[0].size();

    if (obstacleGrid[0][0] || obstacleGrid[n - 1][m - 1])
        return 0;

    vector<vector<long>> dp(n, vector<long>(m, 0));
    dp[n - 1][m - 1] = 1;

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            if ((i == n - 1 && j == m - 1) || obstacleGrid[i][j])
                continue;

            long rans = (j == m - 1) ? 0 : dp[i][j + 1];
            long dans = (i == n - 1) ? 0 : dp[i + 1][j];

            dp[i][j] = rans + dans;
        }
    }
    return dp[0][0];
}