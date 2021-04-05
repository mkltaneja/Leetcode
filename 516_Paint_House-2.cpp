
// METHOD 1 (Recursively)
// TLE

int mincost(int i, int col, vector<vector<int>> &costs)
{
    if (i == costs.size())
        return 0;
    int x = INT_MAX;
    for (int j = 0; j < costs[i].size(); j++)
        if (j != col)
            x = min(x, mincost(i + 1, j, costs) + costs[i][j]);
    return x;
}

int minCost(vector<vector<int>> &costs)
{
    return mincost(0, -1, costs);
}

int mincost(int i, int col, vector<vector<int>> &costs, vector<vector<int>> &dp)
{
    if (i == costs.size() - 1)
        return costs[i][col];
    if (i != -1 && dp[i][col] != INT_MAX)
        return dp[i][col];
    int x = INT_MAX;
    for (int j = 0; j < costs.size(); j++)
        if (j != col)
            x = min(x, mincost(i + 1, j, costs, dp));
    return (i == -1) ? x : (dp[i][col] = x + costs[i][col]);
}

int minCostII(vector<vector<int>> &costs)
{
    int n = costs.size();
    if (n == 0)
        return 0;
    vector<vector<int>> dp(n, vector<int>(3, INT_MAX));
    return mincost(-1, -1, costs, dp);
    // write your code here
}

// METHOD 2 (Memoized)

int mincost(int i, int col, vector<vector<int>> &costs, vector<vector<int>> &dp)
{
    if (i == costs.size() - 1)
        return costs[i][col];
    if (i != -1 && dp[i][col] != INT_MAX)
        return dp[i][col];
    int x = INT_MAX;
    for (int j = 0; j < costs[0].size(); j++)
        if (j != col)
            x = min(x, mincost(i + 1, j, costs, dp));
    return (i == -1) ? x : (dp[i][col] = x + costs[i][col]);
}

int minCostII(vector<vector<int>> &costs)
{
    int n = costs.size();
    if (n == 0)
        return 0;
    vector<vector<int>> dp(n, vector<int>(costs[0].size(), INT_MAX));
    return mincost(-1, -1, costs, dp);
    // write your code here
}

// METHOD 3 (Tabulated)

int mincost(int n, vector<vector<int>> &costs, vector<vector<int>> &dp)
{
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < costs[i].size(); j++)
        {
            int mini = INT_MAX;
            for (int k = 0; k < costs[i].size(); k++)
                if (k != j)
                    mini = min(mini, dp[i + 1][k]);
            dp[i][j] = mini + costs[i][j];
        }
    }

    int mini = INT_MAX;
    for (int i = 0; i < dp[0].size(); i++)
        mini = min(mini, dp[0][i]);
    return mini;
}

int minCostII(vector<vector<int>> &costs)
{
    int n = costs.size();
    if (n == 0)
        return 0;
    vector<vector<int>> dp(n + 1, vector<int>(costs[0].size(), 0));
    return mincost(n, costs, dp);
    // write your code here
}