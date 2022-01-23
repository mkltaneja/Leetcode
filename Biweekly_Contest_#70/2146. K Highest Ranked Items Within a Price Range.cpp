
// APPROACH 1 (Using priority_queue custom comparator)

#define f first
#define s second

struct comp
{
    bool operator()(pair<int, pair<int, pair<int, int>>> &a, pair<int, pair<int, pair<int, int>>> &b)
    {
        if (a.f != b.f)
            return a.f < b.f;
        if (a.s.f != b.s.f)
            return a.s.f < b.s.f;
        if (a.s.s.f != b.s.s.f)
            return a.s.s.f < b.s.s.f;
        return a.s.s.s < b.s.s.s;
    }
};

vector<vector<int>> highestRankedKItems(vector<vector<int>> &grid, vector<int> &pricing, vector<int> &start, int k)
{
    int n = grid.size(), m = grid[0].size();
    priority_queue<pair<int, pair<int, pair<int, int>>>, vector<pair<int, pair<int, pair<int, int>>>>, comp> pq;

    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<vector<int>> vis(n, vector<int>(m, 0));

    queue<pair<int, pair<int, pair<int, int>>>> que;
    que.push({0, {grid[start[0]][start[1]], {start[0], start[1]}}});
    vis[start[0]][start[1]] = 1;
    while (!que.empty())
    {
        auto tp = que.front();
        que.pop();
        if (tp.s.f >= pricing[0] && tp.s.f <= pricing[1])
        {
            pq.push(tp);
            if (pq.size() > k)
                pq.pop();
        }
        for (int d = 0; d < 4; d++)
        {
            int r = tp.s.s.f + dir[d][0];
            int c = tp.s.s.s + dir[d][1];
            if (r >= 0 && c >= 0 && r < n && c < m && !vis[r][c] && grid[r][c])
            {
                vis[r][c] = true;
                que.push({tp.f + 1, {grid[r][c], {r, c}}});
            }
        }
    }

    vector<vector<int>> ans;
    while (!pq.empty())
    {
        ans.push_back({pq.top().s.s.f, pq.top().s.s.s});
        pq.pop();
    }
    reverse(ans.begin(), ans.end());
    return ans;
}


// APPROACH 2 (Sorting) [BETTER]

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