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
