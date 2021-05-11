
#define f first
#define s second
int trapRainWater(vector<vector<int>> &h)
{
    int n = h.size(), m = h[0].size();
    vector<vector<bool>> isboundry(n, vector<bool>(m, false));
    isboundry[0][0] = true, isboundry[0][m - 1] = true;                                                                  // Marking all
    isboundry[n - 1][0] = true, isboundry[n - 1][m - 1] = true;                                                          //corners as boundry
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq; // Min priority Queue

    // Pushing the boundry in the priority queue

    for (int i = 1; i < n - 1; i++)
    {
        pq.push({h[i][0], {i, 0}});
        isboundry[i][0] = true;
    }

    for (int i = 1; i < n - 1; i++)
    {
        pq.push({h[i][m - 1], {i, m - 1}});
        isboundry[i][m - 1] = true;
    }

    for (int j = 1; j < m - 1; j++)
    {
        pq.push({h[0][j], {0, j}});
        isboundry[0][j] = true;
    }

    for (int j = 1; j < m - 1; j++)
    {
        pq.push({h[n - 1][j], {n - 1, j}});
        isboundry[n - 1][j] = true;
    }

    int water = 0;
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    while (!pq.empty())
    {
        auto top = pq.top();
        pq.pop();
        int x = top.f;
        int i = top.s.f, j = top.s.s;
        for (int d = 0; d < 4; d++)
        {
            int r = i + dir[d][0], c = j + dir[d][1];
            if (r < n && c < m && r >= 0 && c >= 0 && !isboundry[r][c])
            {
                isboundry[r][c] = true;
                if (h[r][c] < x)
                {
                    water += (x - h[r][c]);
                    pq.push({x, {r, c}});
                }
                else
                    pq.push({h[r][c], {r, c}});
            }
        }
    }

    return water;
}