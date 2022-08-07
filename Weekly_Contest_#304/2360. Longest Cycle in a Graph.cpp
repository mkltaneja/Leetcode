
int ans = -1;
void dfs(int p, int u, int x, int t, vector<int> &e, vector<int> &vis, unordered_map<int, int> &mp)
{
    vis[u] = t;
    mp[u] = x;

    if (e[u] != -1 && !vis[e[u]])
        dfs(p, e[u], x + 1, t, e, vis, mp);
    else if (e[u] != -1 && vis[e[u]] == t)
        ans = max(ans, mp[u] - mp[e[u]] + 1);
}

int longestCycle(vector<int> &edges)
{
    int n = edges.size();
    unordered_map<int, int> mp;
    vector<int> vis(n, 0);
    int t = 1;
    for (int i = 0; i < n; i++, t++)
        if (!vis[i])
            dfs(i, i, 0, t, edges, vis, mp);
    return ans;
}