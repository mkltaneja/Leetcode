
void dfs(int i, int j, int n, int m, vector<vector<bool>> &vis, vector<vector<int>> &grid, int icolor, int fcolor)
{
    vis[i][j] = true;

    int count = 0;

    if (i + 1 < n)
    {
        if (vis[i + 1][j])
            count++;
        else if (grid[i + 1][j] == icolor)
        {
            count++;
            dfs(i + 1, j, n, m, vis, grid, icolor, fcolor);
        }
    }
    if (j + 1 < m)
    {
        if (vis[i][j + 1])
            count++;
        else if (grid[i][j + 1] == icolor)
        {
            count++;
            dfs(i, j + 1, n, m, vis, grid, icolor, fcolor);
        }
    }
    if (i - 1 >= 0)
    {
        if (vis[i - 1][j])
            count++;
        else if (grid[i - 1][j] == icolor)
        {
            count++;
            dfs(i - 1, j, n, m, vis, grid, icolor, fcolor);
        }
    }
    if (j - 1 >= 0)
    {
        if (vis[i][j - 1])
            count++;
        else if (grid[i][j - 1] == icolor)
        {
            count++;
            dfs(i, j - 1, n, m, vis, grid, icolor, fcolor);
        }
    }

    if (count != 4)
        grid[i][j] = fcolor;
}

vector<vector<int>> colorBorder(vector<vector<int>> &grid, int r0, int c0, int color)
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, false));

    dfs(r0, c0, n, m, vis, grid, grid[r0][c0], color);

    return grid;
}