
bool dfs(int u, vector<int> &vis, vector<vector<int>> &gp)
{
    if (vis[u] != 0)
    {
        if (vis[u] == 1)
            return true;
        if (vis[u] == 2)
            return false;
    }
    vis[u] = 2;
    for (int v : gp[u])
        if (!dfs(v, vis, gp))
            return false;
    vis[u] = 1;

    return true;
}

vector<int> eventualSafeNodes(vector<vector<int>> &graph)
{
    // vis[u] = 0 --> unvisited
    // vis[u] = 1 --> safe
    // vis[u] = 2 --> unsafe

    int n = graph.size();
    vector<int> vis(n, 0);

    for (int i = 0; i < n; i++)
        if (vis[i] == 0)
            dfs(i, vis, graph);

    vector<int> ans;
    for (int i = 0; i < n; i++)
        if (vis[i] == 1)
            ans.push_back(i);

    return ans;
}