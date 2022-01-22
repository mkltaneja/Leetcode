
// APPROACH 2 (Sorting)

#define f first
#define s second

vector<vector<int>> highestRankedKItems(vector<vector<int>> &grid, vector<int> &pricing, vector<int> &start, int k)
{
    int n = grid.size(), m = grid[0].size();

    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<vector<int>> items;

    vector<vector<int>> dist(n, vector<int>(m, 0));
    dist[start[0]][start[1]] = 1;

    queue<pair<int, int>> que;
    que.push({start[0], start[1]});
    while (!que.empty())
    {
        auto tp = que.front();
        que.pop();
        if (grid[tp.f][tp.s] >= pricing[0] && grid[tp.f][tp.s] <= pricing[1])
            items.push_back({dist[tp.f][tp.s], grid[tp.f][tp.s], tp.f, tp.s});
        for (int d = 0; d < 4; d++)
        {
            int r = tp.f + dir[d][0];
            int c = tp.s + dir[d][1];
            if (r < 0 || c < 0 || r == n || c == m || !grid[r][c] || dist[r][c])
                continue;
            dist[r][c] = dist[tp.f][tp.s] + 1;
            que.push({r, c});
        }
    }

    sort(items.begin(), items.end());
    vector<vector<int>> ans;
    for (int i = 0; i < items.size() && k--; i++)
        ans.push_back({items[i][2], items[i][3]});

    return ans;
}