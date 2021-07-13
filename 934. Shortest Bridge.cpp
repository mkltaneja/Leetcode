
#define f first
#define s second

void dfs(int i, int j, int n, int m, vector<vector<int>> &grid, vector<vector<bool>> &vis, queue<pair<pair<int, int>, int>> &que)
{
    vis[i][j] = true;

    int count = 0;
    if (i + 1 < n)
    {
        if (vis[i + 1][j])
            count++;
        else if (grid[i + 1][j] == 1)
        {
            count++;
            dfs(i + 1, j, n, m, grid, vis, que);
        }
    }
    if (j + 1 < m)
    {
        if (vis[i][j + 1])
            count++;
        else if (grid[i][j + 1] == 1)
        {
            count++;
            dfs(i, j + 1, n, m, grid, vis, que);
        }
    }
    if (i - 1 >= 0)
    {
        if (vis[i - 1][j])
            count++;
        else if (grid[i - 1][j] == 1)
        {
            count++;
            dfs(i - 1, j, n, m, grid, vis, que);
        }
    }
    if (j - 1 >= 0)
    {
        if (vis[i][j - 1])
            count++;
        else if (grid[i][j - 1] == 1)
        {
            count++;
            dfs(i, j - 1, n, m, grid, vis, que);
        }
    }

    if (count != 4)
        que.push({{i, j}, 0});
}

int shortestBridge(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();

    queue<pair<pair<int, int>, int>> que;
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    bool found = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
            {
                dfs(i, j, n, m, grid, vis, que);
                found = true;
                break;
            }
        }
        if (found)
            break;
    }

    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    while (!que.empty())
    {
        auto tp = que.front();
        que.pop();
        int i = tp.f.f;
        int j = tp.f.s;

        for (int d = 0; d < 4; d++)
        {
            int r = i + dir[d][0], c = j + dir[d][1];
            if (r == -1 || c == -1 || r == n || c == m || vis[r][c])
                continue;
            if (grid[r][c] == 1)
                return tp.s;
            que.push({{r, c}, tp.s + 1});
            vis[r][c] = true;
        }
    }

    return -1;
}