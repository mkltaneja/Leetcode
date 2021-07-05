
#define f first
#define s second
vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
{
    int n = mat.size(), m = mat[0].size();
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] == 0)
                pq.push({0, {i, j}});

    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    vector<vector<int>> dist(n, vector<int>(m, -1));
    while (!pq.empty())
    {
        auto tp = pq.top();
        pq.pop();
        int i = tp.s.f, j = tp.s.s;

        if (dist[i][j] != -1)
            continue;
        dist[i][j] = tp.f;

        for (int d = 0; d < 4; d++)
        {
            int x = i + dir[d][0], y = j + dir[d][1];
            if (x == -1 || y == -1 || x == n || y == m || dist[x][y] != -1)
                continue;
            pq.push({tp.f + 1, {x, y}});
        }
    }
    return dist;
}