// Method 1 (recursion)
// TLE

int cutType(vector<int> &cuts, int l, int r)
{
    if (l+1 == r)
        return 0;
    int cost = INT_MAX;
    for (int i=l+1; i<r; i++)
    {
        int leftcost = cutType(cuts, l, i);
        int rightcost = cutType(cuts, i, r);
        int len = cuts[r] - cuts[l];

        cost = min(cost, leftcost + rightcost + len);
    }
    return cost;
}

int minCost(int n, vector<int>& cuts)
{
    sort(cuts.begin(), cuts.end());
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);

    return cutType(cuts, 0, cuts.size()-1);
}

// Method 2 (DP)
// AC

int cutType_dp(vector<int> &cuts, int l, int r, vector<vector<int>> &dp)
{
    if (l+1 == r)
        return dp[l][r] = 0;

    if (dp[l][r] != INT_MAX)
        return dp[l][r];

    for (int i=l+1; i<r; i++)
    {
        int leftcost = cutType_dp(cuts, l, i, dp);
        int rightcost = cutType_dp(cuts, i, r, dp);
        int len = cuts[r] - cuts[l];

        dp[l][r] = min(dp[l][r], leftcost + rightcost + len);
    }
    return dp[l][r];
}

int minCost(int n, vector<int>& cuts)
{
    sort(cuts.begin(), cuts.end());
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);
    vector<vector<int>> dp(cuts.size(), vector<int>(cuts.size(), INT_MAX));

    return cutType_dp(cuts, 0, cuts.size()-1, dp);
}

// Method 3 (Tabulation)
// AC

int cutType_tab(vector<int> &cuts, int s, int size, vector<vector<int>> &dp)
{
    for (int gap = 1; gap < size; gap++)
    {
        for (int l = s, r = gap; l < size && r < size; l++, r++)
        {
            if (gap == 1)
            {
                dp[l][r] = 0;
                continue;
            }

            for (int i=l+1; i<r; i++)
            {
                int leftcost = dp[l][i];
                int rightcost = dp[i][r];
                int len = cuts[r] - cuts[l];

                dp[l][r] = min(dp[l][r], leftcost + rightcost + len);
            }
        }
    }
    return dp[s][size-1];
}

int minCost(int n, vector<int>& cuts)
{
    sort(cuts.begin(), cuts.end());
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);
    vector<vector<int>> dp(cuts.size(), vector<int>(cuts.size(), INT_MAX));

    return cutType_tab(cuts, 0, cuts.size(), dp);
}