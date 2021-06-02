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

// DAY 2 (Interleaving Strings)=================================================================================

bool check(int bi, int ci, string &a, string &b, string &c, vector<bool> &vis)
{
    if (bi == b.size())
    {
        string aa = "", bb = "";
        for (int i = 0; i < c.size(); i++)
        {
            if (!vis[i])
                aa += c[i];
            else
                bb += c[i];
        }
        cout << aa << ", " << bb << endl;
        if (aa == a)
            return true;
        return false;
    }
    for (int i = ci; i < c.size(); i++)
    {
        if (c[i] == b[bi] && !vis[i])
        {
            vis[i] = true;
            if (check(bi + 1, i + 1, a, b, c, vis))
                return true;
            vis[i] = false;
        }
    }
    return false;
}

bool isInterleave(string s1, string s2, string s3)
{
    if (s3.size() != s1.size() + s2.size())
        return false;
    vector<bool> vis(s3.size(), false);

    return check(0, 0, s1, s2, s3, vis);
}