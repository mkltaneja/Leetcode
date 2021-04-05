
// APPROACH 1 (Recursively)
int mincost(int i, int col, vector<vector<int>> &costs)
{
    if (i == costs.size())
        return 0;
    int x = INT_MAX;
    for (int j = 0; j < 3; j++)
        if (j != col)
            x = min(x, mincost(i + 1, j, costs) + costs[i][j]);
    return x;
}

int minCost(vector<vector<int>> &costs)
{
    return mincost(0, -1, costs);
}

// METHOD 2 (Memoized (with different approach - storing min ans of next rows in the current row))

int mincost(int i, int col, vector<vector<int>> &costs, vector<vector<int>> &dp)
{
    if (i == costs.size() - 1)
        return costs[i][col];
    if (i != -1 && dp[i][col] != INT_MAX)
        return dp[i][col];
    int x = INT_MAX;
    for (int j = 0; j < 3; j++)
        if (j != col)
            x = min(x, mincost(i + 1, j, costs, dp));
    return (i == -1) ? x : (dp[i][col] = x + costs[i][col]);
}

int minCost(vector<vector<int>> &costs)
{
    int n = costs.size();
    if (n == 0)
        return 0;
    vector<vector<int>> dp(n, vector<int>(3, INT_MAX));
    return mincost(-1, -1, costs, dp);
    // write your code here
}

// METHOD 3 (Tabulation)

int mincost(int n, vector<vector<int>> &costs, vector<vector<int>> &dp)
{
    for (int i = n - 1; i >= 0; i--)
    {
        dp[i][0] = costs[i][0] + min(dp[i + 1][1], dp[i + 1][2]);
        dp[i][1] = costs[i][1] + min(dp[i + 1][0], dp[i + 1][2]);
        dp[i][2] = costs[i][2] + min(dp[i + 1][0], dp[i + 1][1]);
    }
    return min(dp[0][0], min(dp[0][1], dp[0][2]));
}

int minCost(vector<vector<int>> &costs)
{
    int n = costs.size();
    if (n == 0)
        return 0;
    vector<vector<int>> dp(n + 1, vector<int>(3, 0));
    return mincost(n, costs, dp);
    // write your code here
}