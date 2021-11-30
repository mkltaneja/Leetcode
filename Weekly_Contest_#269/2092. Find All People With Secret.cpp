
#define f first
#define s second

vector<int> par;
int findpar(int u)
{
    return par[u] = (par[u] == u) ? u : findpar(par[u]);
}

vector<int> findAllPeople(int n, vector<vector<int>> &meetings, int firstPerson)
{
    par.resize(n);
    for (int i = 0; i < n; i++)
        par[i] = i;
    vector<int> vis(n, 0);
    vis[0] = 1;
    vis[firstPerson] = 1;
    map<int, vector<pair<int, int>>> times;

    for (auto v : meetings)
        times[v[2]].push_back({v[0], v[1]});

    for (auto t : times)
    {
        for (auto p : t.s)
        {
            int p1 = findpar(p.f);
            int p2 = findpar(p.s);
            par[p1] = p2;
            vis[p2] |= vis[p1];
        }
        for (auto p : t.s)
        {
            vis[p.f] |= vis[findpar(p.f)];
            vis[p.s] |= vis[findpar(p.s)];
        }
        for (auto p : t.s)
        {
            par[p.f] = p.f;
            par[p.s] = p.s;
        }
    }

    vector<int> ans;
    for (int i = 0; i < n; i++)
        if (vis[i])
            ans.push_back(i);

    return ans;
}

// DAY 28 (797. All Paths From Source to Target)=========================================================

// APPROACH 1 (DFS)

vector<vector<int>> ans;
void dfs(int u, int n, vector<vector<int>> &gp, vector<int> &path)
{
    if (u == n - 1)
        ans.push_back(path);
    for (int v : gp[u])
    {
        path.push_back(v);
        dfs(v, n, gp, path);
        path.pop_back();
    }
}

vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<int> path;
    path.push_back(0);
    dfs(0, n, graph, path);

    return ans;
}

// APPROACH 2 (BFS)

#define f first
#define s second
vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<vector<int>> ans;
    vector<bool> vis(n);

    queue<pair<int, vector<int>>> que;
    que.push({0, {0}});
    while (!que.empty())
    {
        auto tp = que.front();
        que.pop();

        if (tp.f == n - 1)
            ans.push_back(tp.s);

        for (int v : graph[tp.f])
        {
            tp.s.push_back(v);
            que.push({v, {tp.s}});
            tp.s.pop_back();
        }
    }

    return ans;
}
