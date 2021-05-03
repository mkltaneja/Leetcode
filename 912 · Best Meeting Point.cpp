
int minTotalDistance(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    vector<int> rows, cols;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
            {
                rows.push_back(i);
                cols.push_back(j);
            }
        }
    }
    sort(rows.begin(), rows.end());
    sort(cols.begin(), cols.end());
    int r = rows[rows.size() / 2], c = cols[cols.size() / 2];
    // cout<<r<<", "<<c<<endl;
    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j])
                ans += abs(i - r) + abs(j - c);

    return ans;
}