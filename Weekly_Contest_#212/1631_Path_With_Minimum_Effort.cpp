
#define f first
#define s second

int minimumEffortPath(vector<vector<int>> &heights)
{
    int n = heights.size();
    int m = heights[0].size();
    int max = 1e6, min = -1;
    vector<vector<int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    while (min + 1 < max)
    {
        int mid = (max + min) / 2;
        vector<vector<bool>> vis(n, vector<bool>(m, 0));
        vis[0][0] = true;
        queue<pair<int, int>> que;
        que.push({0, 0});
        while (!que.empty())
        {
            int pi = que.front().f;
            int pj = que.front().s;
            que.pop();
            for (int d = 0; d < 4; d++)
            {
                int i = pi + dir[d][0];
                int j = pj + dir[d][1];
                if (i < n && i >= 0 && j < m && j >= 0 && !vis[i][j] && abs(heights[i][j] - heights[pi][pj]) <= mid)
                {
                    que.push({i, j});
                    vis[i][j] = true;
                }
            }
        }
        if (vis[n - 1][m - 1])
            max = mid;
        else
            min = mid;
    }
    return max;
}