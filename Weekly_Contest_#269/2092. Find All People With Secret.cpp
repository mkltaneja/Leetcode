
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
