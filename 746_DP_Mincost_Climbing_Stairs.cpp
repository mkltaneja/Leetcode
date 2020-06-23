// RECURSION
// TLE
int dp_ways(int n, vector<int> cost, vector<int> &dp)
{
    if (n <= 1)
    {
        return dp[n] = cost[n];
    }
    if (dp[n] != 0)
        return dp[n];

    int tcost = cost[n] + min(dp_ways(n - 1, cost, dp), dp_ways(n - 2, cost, dp));
    return dp[n] = tcost;
}

int minCostClimbingStairs(vector<int> &cost)
{
    int n = cost.size();
    cost.push_back(0); // to make recursion easy
    vector<int> dp(n + 1, 0);
    return dp_ways(n, cost, dp);
}

// DP
// accepted
int rec_ways(int n, vector<int> cost)
{
    if (n <= 1)
    {
        return cost[n];
    }

    int tcost = cost[n] + min(rec_ways(n - 1, cost), rec_ways(n - 2, cost));
    return tcost;
}

int minCostClimbingStairs(vector<int> &cost)
{
    int n = cost.size();
    cost.push_back(0); // to make recursion easy
    return rec_ways(n, cost);
} 

// TABULATION
// accepted
int tab_ways(int n, vector<int> cost, vector<int> &dp)
{
    for (int i = 0; i <= n; i++)
    {
        if (i <= 1)
        {
            dp[i] = cost[i];
            continue;
        }
        dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]);
    }
    return dp[n];
}

int minCostClimbingStairs(vector<int> &cost)
{
    int n = cost.size();
    cost.push_back(0); // to make recursion easy
    vector<int> dp(n + 1, 0);
    return tab_ways(n, cost, dp);
}