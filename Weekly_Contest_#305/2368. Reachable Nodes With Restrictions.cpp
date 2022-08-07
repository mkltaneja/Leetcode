

int dfs(int p, int u, vector<vector<int>> &gp, unordered_set<int> &st)
{
    int ans = 0;
    for (int v : gp[u])
        if (v != p && !st.count(v))
            ans += dfs(u, v, gp, st);

    return ans + 1;
}

int reachableNodes(int n, vector<vector<int>> &edges, vector<int> &restricted)
{
    unordered_set<int> st;
    for (int x : restricted)
        st.insert(x);

    vector<vector<int>> gp(n);
    for (auto v : edges)
    {
        gp[v[0]].push_back(v[1]);
        gp[v[1]].push_back(v[0]);
    }

    return dfs(-1, 0, gp, st);
}