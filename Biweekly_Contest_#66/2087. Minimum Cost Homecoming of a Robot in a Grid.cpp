
// APPROACH 1 (Using Dijikstra) 
// TLE

#define f first
#define s second

int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

int bfs(int ii, int ij, int fi, int fj, int n, int m, vector<vector<int>> &minc, vector<int> &rc, vector<int> &cc)
{
    pq.push({0, {ii, ij}});
    minc[ii][ij] = 0;
    while (!pq.empty())
    {
        int i = pq.top().s.f;
        int j = pq.top().s.s;
        int x = pq.top().f;
        pq.pop();
        // cout<<i<<", "<<j<<", "<<x<<endl;

        if (i == fi && j == fj)
            return x;

        for (int d = 0; d < 4; d++)
        {
            int r = i + dir[d][0], c = j + dir[d][1];
            if (r == -1 || c == -1 || r == n || c == m)
                continue;
            int y = ((r == i) ? 0 : rc[r]) + ((c == j) ? 0 : cc[c]);
            if (minc[r][c] <= x + y)
                continue;
            minc[r][c] = x + y;
            pq.push({x + y, {r, c}});
        }
    }
    return -1;
}

int minCost(vector<int> &st, vector<int> &end, vector<int> &rc, vector<int> &cc)
{
    int n = rc.size(), m = cc.size();
    vector<vector<int>> mincost(n, vector<int>(m, INT_MAX));
    // cout<<endl;
    return bfs(st[0], st[1], end[0], end[1], n, m, mincost, rc, cc);
}