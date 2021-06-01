// DAY 1 (Max Area of Island)=============================================================

int dfs(int i, int j, int n, int m, vector<vector<int>> &grid)
{
    if (i == -1 || j == -1 || i == n || j == m || !grid[i][j])
        return 0;

    int area = 0;
    grid[i][j] = 0;

    return dfs(i + 1, j, n, m, grid) +
           dfs(i, j + 1, n, m, grid) +
           dfs(i - 1, j, n, m, grid) +
           dfs(i, j - 1, n, m, grid) + 1;
}

int maxAreaOfIsland(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    int maxarea = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j])
                maxarea = max(maxarea, dfs(i, j, n, m, grid));
    return maxarea;
}