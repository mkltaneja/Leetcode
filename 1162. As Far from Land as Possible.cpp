
#define f first
#define s second

int findDist(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int maxDistance(vector<vector<int>> &mat)
{
    int n = mat.size(), m = mat[0].size();
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == 1)
                pq.push({0, {i, j}});

    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    vector<vector<int>> dist(n, vector<int>(m, -1));
    int ans = -1;
    while (!pq.empty())
    {
        auto tp = pq.top();
        pq.pop();
        int i = tp.s.f, j = tp.s.s;

        if (dist[i][j] != -1)
            continue;
        dist[i][j] = tp.f;

        if (mat[i][j] == 0)
            ans = max(ans, tp.f);

        for (int d = 0; d < 4; d++)
        {
            int x = i + dir[d][0], y = j + dir[d][1];
            if (x == -1 || y == -1 || x == n || y == m || dist[x][y] != -1)
                continue;
            pq.push({tp.f + findDist(i, j, x, y), {x, y}});
        }
    }
    return ans;
}