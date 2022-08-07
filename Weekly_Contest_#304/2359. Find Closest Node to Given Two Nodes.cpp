
void dfs(int x, int u, vector<int> &e, unordered_map<int, int> &mp1, vector<int> &vis)
{
    vis[u] = 1;
    mp1[u] = x;
    if (e[u] != -1 && !vis[e[u]])
        dfs(x + 1, e[u], e, mp1, vis);
}

int closestMeetingNode(vector<int> &edges, int node1, int node2)
{
    int n = edges.size();
    unordered_map<int, int> mp1, mp2;

    vector<int> vis(n, 0);
    dfs(0, node1, edges, mp1, vis);
    vis.assign(n, 0);
    dfs(0, node2, edges, mp2, vis);

    int ansi = INT_MAX, mindist = INT_MAX;
    for (auto p : mp1)
    {
        if (mp2.count(p.first))
        {
            int dist = max(p.second, mp2[p.first]);
            if (mindist > dist)
            {
                mindist = dist;
                ansi = p.first;
            }
            else if (mindist == dist)
                ansi = min(ansi, p.first);
        }
    }

    return ansi == INT_MAX ? -1 : ansi;
}