
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