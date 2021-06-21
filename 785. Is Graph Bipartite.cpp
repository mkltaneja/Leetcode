
#define f first
#define s second

bool checkBipartite(int u, vector<int> &color, vector<vector<int>> &graph)
{
    queue<pair<int, int>> que;

    que.push({u, 0});
    color[u] = 0;

    while (!que.empty())
    {
        auto p = que.front();
        que.pop();
        for (int v : graph[p.f])
        {
            if (color[v] == p.s)
                return false;
            if (color[v] == -1)
            {
                color[v] = (p.s + 1) % 2;
                que.push({v, color[v]});
            }
        }
    }
    return true;
}

bool isBipartite(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<int> color(n, -1);
    for (int i = 0; i < n; i++)
        if (color[i] == -1)
            if (!checkBipartite(i, color, graph))
                return false;
    return true;
}