
void dfs(int i, int j, vector<vector<int>> &grid)
{
    if (i == -1 || j == -1 || i == grid.size() || j == grid[0].size() || grid[i][j] == 0)
        return;

    grid[i][j] = 0;

    dfs(i + 1, j, grid);
    dfs(i, j + 1, grid);
    dfs(i - 1, j, grid);
    dfs(i, j - 1, grid);
}

void removeInvalid(int n, int m, vector<vector<int>> &grid)
{
    for (int i = 0; i < n; i++)
        dfs(i, 0, grid);
    for (int i = 0; i < n; i++)
        dfs(i, m - 1, grid);
    for (int i = 0; i < m; i++)
        dfs(0, i, grid);
    for (int i = 0; i < m; i++)
        dfs(n - 1, i, grid);
}

int numEnclaves(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    removeInvalid(n, m, grid);

    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 1)
                cnt++;
    return cnt;
}