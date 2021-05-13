
int largestPathValue(string colors, vector<vector<int>> &edges)
{
    int n = colors.size();
    vector<vector<int>> gp(n);
    vector<int> indeg(n, 0);
    for (auto v : edges)
    {
        indeg[v[1]]++;
        gp[v[0]].push_back(v[1]);
    }
    queue<int> que;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0)
            que.push(i);
    vector<vector<int>> colorcnt(n, vector<int>(26, 0));
    int ans = 0;
    int nodes = 0;
    while (!que.empty())
    {
        int u = que.front();
        que.pop();
        nodes++;
        ans = max(ans, ++colorcnt[u][colors[u] - 'a']);
        for (int v : gp[u])
        {
            for (int c = 0; c < 26; c++)
                colorcnt[v][c] = max(colorcnt[v][c], colorcnt[u][c]);
            if (--indeg[v] == 0)
                que.push(v);
        }
    }
    return (nodes != n) ? -1 : ans;
}