
#define f first
#define s second

int swimInWater(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    pq.push({grid[0][0], {0, 0}});
    vector<vector<bool>> vis(n, vector<bool>(n, false));

    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    while (!pq.empty())
    {
        auto tp = pq.top();
        pq.pop();

        if (tp.s.f == n - 1 && tp.s.s == m - 1)
            return tp.f;

        if (vis[tp.s.f][tp.s.s])
            continue;
        vis[tp.s.f][tp.s.s] = true;

        for (int d = 0; d < 4; d++)
        {
            int i = tp.s.f + dir[d][0];
            int j = tp.s.s + dir[d][1];

            if (i != -1 && j != -1 && i != n && j != m && !vis[i][j])
                pq.push({max(tp.f, grid[i][j]), {i, j}});
        }
    }
    return -1;
}