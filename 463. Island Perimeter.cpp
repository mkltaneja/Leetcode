
int islandPerimeter(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j])
            {
                int u = (i && grid[i - 1][j]) ? 0 : 1;
                int l = (j && grid[i][j - 1]) ? 0 : 1;
                int d = (i != n - 1 && grid[i + 1][j]) ? 0 : 1;
                int r = (j != m - 1 && grid[i][j + 1]) ? 0 : 1;

                ans += l + r + d + u;
            }
        }
    }
    return ans;
}