
#define f first
#define s second
int orangesRotting(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    queue<pair<int, int>> que;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 2)
                que.push({i, j});

    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    int time = 0;
    while (!que.empty())
    {
        bool pushed = false;
        int sz = que.size();
        while (sz--)
        {
            auto tp = que.front();
            que.pop();
            int r = tp.f, c = tp.s;
            for (int d = 0; d < 4; d++)
            {
                int x = r + dir[d][0], y = c + dir[d][1];
                if (x < n && y < m && x >= 0 && y >= 0 && grid[x][y] == 1)
                {
                    grid[x][y] = 2;
                    que.push({x, y});
                    pushed = true;
                }
            }
        }
        if (pushed)
            time++;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 1)
                return -1;
    return time;
}