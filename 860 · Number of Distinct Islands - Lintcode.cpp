
void dfs(int i, int j, vector<vector<int>> &grid, string &shape)
{
    grid[i][j] = 0;

    if (i + 1 < grid.size() && grid[i + 1][j] == 1)
    {
        shape += "D";
        dfs(i + 1, j, grid, shape);
    }
    if (j + 1 < grid[0].size() && grid[i][j + 1] == 1)
    {
        shape += "R";
        dfs(i, j + 1, grid, shape);
    }
    if (i - 1 >= 0 && grid[i - 1][j] == 1)
    {
        shape += "U";
        dfs(i - 1, j, grid, shape);
    }
    if (j - 1 >= 0 && grid[i][j - 1] == 1)
    {
        shape += "L";
        dfs(i, j - 1, grid, shape);
    }
    shape += "B";
}

int numberofDistinctIslands(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    set<string> ans;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
            {
                string shape = "";
                dfs(i, j, grid, shape);
                ans.insert(shape);
            }
        }
    }
    return ans.size();
}