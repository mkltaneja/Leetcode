
int minFallingPathSum(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    int minans = INT_MAX;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            if (i == n - 1)
                dp[i][j] = matrix[i][j];
            else
            {
                int rans = (j == m - 1) ? INT_MAX : dp[i + 1][j + 1];
                int lans = (!j) ? INT_MAX : dp[i + 1][j - 1];
                int dans = dp[i + 1][j];
                dp[i][j] = min({lans, rans, dans}) + matrix[i][j];
            }

            if (i == 0)
                minans = min(minans, dp[i][j]);
        }
    }
    return minans;
}