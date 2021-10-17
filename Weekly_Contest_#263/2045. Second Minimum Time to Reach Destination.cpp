
#define f first
#define s second

struct comp
{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b)
    {
        return a.s > b.s;
    }
};

int secondMinimum(int n, vector<vector<int>> &edges, int t, int c)
{
    vector<vector<int>> gp(n);
    for (auto v : edges)
    {
        gp[v[0] - 1].push_back(v[1] - 1);
        gp[v[1] - 1].push_back(v[0] - 1);
    }

    vector<bool> vis(n);
    vector<vector<int>> best(n, vector<int>(2, INT_MAX));
    priority_queue<pair<int, int>, vector<pair<int, int>>, comp> pq;
    pq.push({0, 0});
    vis[0] = true;
    while (!pq.empty())
    {
        auto [u, tt] = pq.top();
        pq.pop();

        if (best[u][1] <= tt)
            continue;
        if (best[u][0] == tt)
            continue;

        if (best[u][0] > tt)
        {
            best[u][1] = best[u][0];
            best[u][0] = tt;
        }
        else if (best[u][1] > tt)
            best[u][1] = tt;

        if ((tt / c) & 1)
            tt += (((tt / c) + 1) * c - tt) + t;
        else
            tt += t;
        for (int v : gp[u])
            pq.push({v, tt});
    }

    return best[n - 1][1];
}